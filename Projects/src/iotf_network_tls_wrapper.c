/*******************************************************************************
 * Copyright (c) 2017 IBM Corp.
 *
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * and Eclipse Distribution License v1.0 which accompany this distribution.
 *
 * The Eclipse Public License is available at
 *    http://www.eclipse.org/legal/epl-v10.html
 * and the Eclipse Distribution License is available at
 *   http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * Contributors:
 *    Lokesh Haralakatta  -  Initial implementation
 *    Lokesh Haralakatta  -  Added Logging Feature
 *******************************************************************************/
#include "main.h"
#include "iotf_network_tls_wrapper.h"

/** Function to check whether the given timer is expired or not
* @param - Address of Timer
* @return - 0 or 1
**/
char has_timer_expired(Timer*);
void init_timer(Timer *timer);

 char expired(Timer* timer)
 {
  return has_timer_expired(timer);
 }

 /** Function to update timer with given timeout value in seconds
 * @param - Address of Timer and timeout in seconds
 * @return - void
 **/
 void countdown(Timer* timer, unsigned int timeout)
 {
  countdown_ms(timer,    1000*timeout);
 }

 
 /** Function to initialize the Timer Structure variable
 * @param - Address of Timer
 * @return - void
 **/
 void InitTimer(Timer* timer)
 {
  init_timer(timer);
 }

 
 
 
 /** Function to initialize Network structure with defualt values and network functions
* @param - Address of Network Structure Variable
* @return - void
**/
void NewNetwork(Network* n)
{
       n->my_socket = 0;
       n->mqttread = network_read;
       n->mqttwrite = network_write;
       n->disconnect = network_disconnect;
       n->TLSConnectData.pServerCertLocation = NULL;
       n->TLSConnectData.pRootCACertLocation = NULL;
       n->TLSConnectData.pDeviceCertLocation = NULL;
       n->TLSConnectData.pDevicePrivateKeyLocation = NULL;
       n->TLSConnectData.pDestinationURL = NULL;
}


 /** Function to establish connection to given host address and port without SSL/TLS
 * @param - Address of Network Structure
 *        - Host Address to connect
 *        - Port number to connect
 * @return - 0 for SUCCESS
 *         - -1 for FAILURE
 **/
 int ConnectNetwork(Network* n, char* addr, int port)
 {
  int rc = 0;
        
  if( (rc = net_sock_create(hnet, (net_sockhnd_t *)&n->my_socket, NET_PROTO_TCP)) != NET_OK )
  {
    msg_error(" failed to create a TCP socket  ! net_sock_create %d\n", rc);
    return rc;
  }

  if( (rc = net_sock_setopt(n->my_socket, "sock_noblocking", NULL, 0)) != NET_OK )
   {
     msg_error(" failed to set the TCP socket noblocking ! net_sock_setopt %d\n", rc);
     return rc;
   }
  
  if((rc = net_sock_open(n->my_socket, addr, port)) != NET_OK)
  {
//    sprintf(logHdr,"%s:%d:%s:",__FILE__,__LINE__,__func__);
//    sprintf(logStr,"RC from connect - %d :",rc);
//    LOG(logHdr,logStr);
   }

   return rc;
 }

 /** Function to read data from the socket opened into provided buffer
 * @param - Address of Network Structure
 *        - Buffer to store the data read from socket
 *        - Expected number of bytes to read from socket
 *        - Timeout in milliseconds
 * @return - Number of Bytes read on SUCCESS
 *         - -1 on FAILURE
 **/
 int network_read(Network* n, unsigned char* buffer, int len, int timeout_ms)
 {
   int bytes;

   bytes = net_sock_recv((net_sockhnd_t) n->my_socket, buffer, len);
   if(bytes < 0)
   {
     bytes = -1;
   }

   return bytes;
 }

 /** Function to write data to the socket opened present in provided buffer
 * @param - Address of Network Structure
 *        - Buffer storing the data to write to socket
 *        - Number of bytes of data to write to socket
 *        - Timeout in milliseconds
 * @return - Number of Bytes written on SUCCESS
 *         - -1 on FAILURE
 **/
 int network_write(Network* n, unsigned char* buffer, int len, int timeout_ms)
 {
   int rc;

   rc = net_sock_send((net_sockhnd_t) n->my_socket, buffer, len);
   if(rc < 0)
   {
     rc = -1;
   }

   return rc;
 }
 
 
/** Function to connect to given server using SSL/TLS secured connection. If useClientCerts Flag
* is set, then it uses the specified Client Side Certificates for communication.
* @param - Address of tls_init_larams structure
*        - Address of tls_connect_params structure
*        - Server Address
*        - Port Number
*        - whether to use client side certificates or not
* @return - 1 on SUCCESS
*         - -1 on FAILURE
**/

#define NET_READ_TIMEOUT  "1000"
//#define NET_WRITE_TIMEOUT  "1000"
 
int 
tls_connect(tls_init_params *tlsInitData,tls_connect_params *tlsConnectData,
                const char *server, const int port, int useClientCerts)
{
  net_sockhnd_t socket;

  int ret = net_sock_create(hnet, &socket, NET_PROTO_TLS);
  if (ret != NET_OK)
  {
    msg_error("Could not create the socket.\n");
  }
  else
  {
    tlsInitData->server_fd.fd = (int) socket;
//    ret |= net_sock_setopt(socket, "sock_read_timeout", NET_READ_TIMEOUT, sizeof(NET_READ_TIMEOUT));
    ret |= net_sock_setopt(socket, "sock_noblocking", NULL, 0);

//    ret |= net_sock_setopt(socket, "sock_write_timeout", NET_WRITE_TIMEOUT, sizeof(NET_WRITE_TIMEOUT));
 
    ret |= net_sock_setopt(socket, "tls_ca_certs", (void *)tlsConnectData->pServerCertLocation, strlen(tlsConnectData->pServerCertLocation));
    ret |= net_sock_setopt(socket, "tls_server_name", (void*) tlsConnectData->pDestinationURL, strlen(tlsConnectData->pDestinationURL)+1);
    
    if ((tlsConnectData->pServerCertLocation!=NULL) && (tlsConnectData->pDeviceCertLocation!=NULL) && (tlsConnectData->pDevicePrivateKeyLocation!=NULL) && (tlsConnectData->pDestinationURL!=NULL))
    {
      ret |= net_sock_setopt(socket, "tls_ca_certs", (void *)tlsConnectData->pServerCertLocation, strlen(tlsConnectData->pServerCertLocation));
      ret |= net_sock_setopt(socket, "tls_server_name", (void*) tlsConnectData->pDestinationURL, strlen(tlsConnectData->pDestinationURL)+1);
      ret |= net_sock_setopt(socket, "tls_dev_cert", (void*) tlsConnectData->pDeviceCertLocation, strlen(tlsConnectData->pDeviceCertLocation));
      ret |= net_sock_setopt(socket, "tls_dev_key", (void*) tlsConnectData->pDevicePrivateKeyLocation, strlen(tlsConnectData->pDevicePrivateKeyLocation));
      ret |= net_sock_setopt(socket, "tls_dev_pwd", NULL, 0);
    }
    
//mbedtls_ssl_conf_max_version(&(tlsInitData->conf),MBEDTLS_SSL_MAJOR_VERSION_3,MBEDTLS_SSL_MINOR_VERSION_3);
//       mbedtls_ssl_conf_min_version(&(tlsInitData->conf),MBEDTLS_SSL_MAJOR_VERSION_3,MBEDTLS_SSL_MINOR_VERSION_3);
    // -> move to MBEDTLS_SSL_PRESET_SUITEB?
  }
  
  if (ret != NET_OK)
  {
    msg_error("Could not set the socket options.\n");
  }
  else
  {
    ret = net_sock_open(socket,server, port);
  }
  
  if (ret != NET_OK)
  {
    msg_error("Could not open the socket at %s port %d.\n",server,port);
  }
    
  return 0;

}
 
 
 /** Function used to close the opened socket for communication. If the given mode is quick start,
 it just closes the socket opened otherwise it calls teardown_tls function to cleanup mbedtls structures.
 * @param - Address of Network Structure
 * @return - void
 **/
 void network_disconnect(Network* n)
 {
   int ret;
   ret = net_sock_close(n->my_socket);
   ret |= net_sock_destroy(n->my_socket);
   if (ret != NET_OK)
   {
          msg_error("net_sock_close() or net_sock_destroy() failed.\n");
   }
 }

 /** Function to initialize mbedtls structures. If useClientCerts flag is 1,
 * then certificate related structure gets initialized.
 * @param - Address of tls_init Structure
 *        - Flag to indicate whether to use client certificates or not
 * @return - 0 on SUCCESS
 *         - -1 on FAILURE
 **/

 /** Function to read data from the secured tls socket
 * @param - Address of Network Structure
 *        - Buffer to store the read data from the secured socket
 *        - Number of bytes of data to read from secured socket
 *        - Timeout in milliseconds
 * @return - Number of Bytes read on SUCCESS
 *         - -1 on FAILURE
 **/
 
 int tls_read(Network* n, unsigned char* buffer, int len, int timeout_ms)
 {
       return network_read(n,buffer,len,timeout_ms);
 }
 
 /** Function to write data to the secured tls socket
 * @param - Address of Network Structure
 *        - Buffer storing the data to write to the secured socket
 *        - Number of bytes of data to write to secured socket
 *        - Timeout in milliseconds
 * @return - Number of Bytes written on SUCCESS
 *         - -1 on FAILURE
 **/
 int tls_write(Network* n, unsigned char* buffer, int len, int timeout_ms)
 {
         return network_write(n,buffer,len,timeout_ms);
 }
    

 /** Function to clear off the memory allocated for certificates location.
 * @param - Address of tls_connect Structure
 * @return - void
 **/
void freeTLSConnectData(tls_connect_params* tlsConnectData){
        free(tlsConnectData->pServerCertLocation);
        free(tlsConnectData->pRootCACertLocation);
        free(tlsConnectData->pDeviceCertLocation);
        free(tlsConnectData->pDevicePrivateKeyLocation);
        free(tlsConnectData->pDestinationURL);
}
