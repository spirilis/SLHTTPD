///
/// @file SLHTTPD.h
/// @brief   Header
/// @headerfile <>
/// @details SimpleLink HTTP Server
///          @n Supports the NetApp HTTP Server on TI CC3100/CC3200 WiFi Network Processors
///          @n Tested on TI MSP430F5529 LaunchPad + CC3100 BoosterPack
///
/// @author    Eric Brundick for the Energia project
///
/// @date      2016
/// @version   101
///
/// @copyright  (C) 2016 Eric Brundick spirilis at linux dot com
///  @n GNU Lesser General Public License
///  @n
///  @n This library is free software; you can redistribute it and/or
///  @n modify it under the terms of the GNU Lesser General Public
///  @n License as published by the Free Software Foundation; either
///  @n version 2.1 of the License, or (at your option) any later version.
///  @n
///  @n This library is distributed in the hope that it will be useful,
///  @n but WITHOUT ANY WARRANTY; without even the implied warranty of
///  @n MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
///  @n Lesser General Public License for more details.
///  @n
///  @n You should have received a copy of the GNU Lesser General Public
///  @n License along with this library; if not, write to the Free Software
///  @n Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

#ifndef SLHTTPD_H
#define SLHTTPD_H

#include <Energia.h>
#include <WiFi.h>


// User token callbacks
///
/// @brief User callback function type for GET token requests
typedef size_t(*UserGetTokenCallback)(const char *, void *);
/// @brief User callback function type for POST token requests
typedef void(*UserPostTokenCallback)(const char *, const void *, const size_t);
///

// Token linked-list type
typedef struct {
    char id[3];
    size_t counter;
    UserGetTokenCallback callback;
    UserGetTokenList *next;
} UserGetTokenList;

typedef struct {
    char id[3];
    size_t counter;
    UserPostTokenCallback callback;
    UserPostTokenList *next;
} UserPostTokenList;



class SLHTTPD {
    private:
        size_t tokenstats_get, tokenstats_post;
        UserGetTokenList *tokenGetRegistry;
        UserPostTokenList *tokenPostRegistry;

    public:
        SLHTTPD();  ///< Constructor, inits private data structures

        ///
        /// @brief Internal event callback handler
        void EventCallback(SlHttpServerEvent_t *pSlHttpServerEvent, SlHttpServerResponse_t *pSlHttpServerResponse);

        ///
        /// @defgroup server_admin Server Administration Functions
        /// @{

        ///
        /// @brief Initialize HTTP Server
        void begin(void);

        ///
        /// @brief Switch off HTTP Server
        void end(void);

        ///
        /// @brief Retrieve current configured port
        uint16_t getPort(void);

        ///
        /// @brief Set HTTP server port
        int32_t setPort(uint16_t p);

        ///
        /// @brief Set current hostname
        int32_t setHostname(const uint8_t *hostname);
        int32_t setHostname(const char *hostname) { return setHostname((const uint8_t *)hostname); };
        int32_t setHostname(String hostname) { return setHostname((const uint8_t *)hostname.c_str()); };

        ///
        /// @brief Get current hostname
        int32_t getHostname(void *buf, const size_t maxlen);

        ///
        /// @brief Switch ROM page lookup on/off
        int32_t useRomPages(boolean yesno);

        ///
        /// @brief Switch mDNS service on/off
        int32_t use_mDNS(boolean yesno);
        /// @}
        ///


        ///
        /// @defgroup callback_admin HTTP Token Callback Administration
        /// @{

        ///
        /// @brief Pull statistics on global # of GET token requests
        size_t getUserTokenHitsGET(void);
        /// @brief Pull statistics on GET requests for a specific token
        size_t getUserTokenHitsGET(const uint8_t *token);
        size_t getUserTokenHitsGET(const char *token) { return getUserTokenHitsGET((const uint8_t *)token); };
        size_t getUserTokenHitsGET(String token) { return getUserTokenHitsGET((const uint8_t *)token.c_str()); };

        ///
        /// @brief Pull statistics on global # of POST token requests
        size_t getUserTokenHitsPOST(void);
        /// @brief Pull statistics on POST requests for a specific token
        size_t getUserTokenHitsPOST(const uint8_t *token);
        size_t getUserTokenHitsPOST(const char *token) { return getUserTokenHitsPOST((const uint8_t *)token); };
        size_t getUserTokenHitsPOST(String token) { return getUserTokenHitsPOST((const uint8_t *)token.c_str()); };

        ///
        /// @brief Register a user GET token with callback
        int32_t registerGetToken(const uint8_t * token, UserGetTokenCallback cb);
        int32_t registerGetToken(const char * token, UserGetTokenCallback cb) { return registerGetToken((const uint8_t *)token, cb); };
        int32_t registerGetToken(String token, UserGetTokenCallback cb) { return registerGetToken((const uint8_t *)token.c_str(), cb); };

        ///
        /// @brief Deregister a user GET token
        int32_t deregisterGetToken(const uint8_t *token);
        int32_t deregisterGetToken(const char * token) { return deregisterGetToken((const uint8_t *)token); };
        int32_t deregisterGetToken(String token) { return deregisterGetToken((const uint8_t *)token.c_str()); };

        ///
        /// @brief Register a user POST token with callback
        int32_t registerPostToken(const uint8_t *token, UserPostTokenCallback cb);
        int32_t registerPostToken(const char *token, UserPostTokenCallback cb) { return registerPostToken((const uint8_t *)token, cb); };
        int32_t registerPostToken(String token, UserPostTokenCallback cb) { return registerPostToken((const uint8_t *)token.c_str(), cb); };

        ///
        /// @brief Deregister a user POST token
        int32_t deregisterPostToken(const uint8_t *token);
        int32_t deregisterPostToken(const char * token) { return deregisterPostToken((const uint8_t *)token); };
        int32_t deregisterPostToken(String token) { return deregisterPostToken((const uint8_t *)token.c_str()); };
        /// @}
        ///
};

#endif /* SLHTTPD_H */
