/*********************************************************
 * Copyright (C) 2007-2018 VMware, Inc. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation version 2 and no later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA  02110-1301 USA
 *
 *********************************************************/

/*
 * vsockSocketWrapper.h --
 *
 *    Socket wrapper constants, types and functions.
 */


#ifndef _VSOCK_SOCKET_WRAPPER_H_
#define _VSOCK_SOCKET_WRAPPER_H_

/*
 * Socket states and flags.  Note that MSG_WAITALL is only defined on 2K3,
 * XP-SP2 and above.  Since we currently build for 2K to maintain backwards
 * compatibility, we pull the value from the newer header.  Same for the
 * POLLXXX flags, which are not defined before Vista.
 */
#if defined(_WIN32)
#  define MSG_DONTWAIT        0
#  define MSG_NOSIGNAL        0
#  if (_WIN32_WINNT < 0x0502)
#     define MSG_WAITALL      0x8
#  endif
#  if (_WIN32_WINNT < 0x0600)
#     define POLLRDNORM       0x0100
#     define POLLRDBAND       0x0200
#     define POLLIN           (POLLRDNORM | POLLRDBAND)
#     define POLLPRI          0x0400
#     define POLLWRNORM       0x0010
#     define POLLOUT          (POLLWRNORM)
#     define POLLWRBAND       0x0020
#     define POLLERR          0x0001
#     define POLLHUP          0x0002
#     define POLLNVAL         0x0004
#  endif
#endif

#if defined __APPLE__
#  define MSG_NOSIGNAL			0

/*
 * Custom options for setting socket behavious in kVsockSetOptions.
 * These values fall after the common Mac OS X Socket options
 * in /usr/inclue/sys/socket.h
 */
#define SO_NONBLOCKING  0x1200
#endif // __APPLE__

#if defined(_WIN32) || defined(VMKERNEL) || defined(__APPLE__) || defined(VMX86_VMX)
#  define SS_FREE             0
#  define SS_UNCONNECTED      1
#  define SS_CONNECTING       2
#  define SS_CONNECTED        3
#  define SS_DISCONNECTING    4
#  define SS_DISCONNECTED     5
#  define RCV_SHUTDOWN        1
#  define SEND_SHUTDOWN       2
#  define SHUTDOWN_MASK       3
#endif // _WIN32 || VMKERNEL

/*
 * For signalling sockets.  These are defined as standard on Windows.  We do
 * not use them on Linux.  So define them here only for VMKernel.
 */
#if defined(_WIN32)
#  define SOCKET_EVENT_READ    FD_READ
#  define SOCKET_EVENT_WRITE   FD_WRITE
#  define SOCKET_EVENT_ACCEPT  FD_ACCEPT
#  define SOCKET_EVENT_CONNECT FD_CONNECT
#  define SOCKET_EVENT_CLOSE   FD_CLOSE
#else
#if defined(VMKERNEL)  || defined(__APPLE__) || defined(VMX86_VMX)
#  define SOCKET_EVENT_READ    0x1
#  define SOCKET_EVENT_WRITE   0x2
#  define SOCKET_EVENT_ACCEPT  0x8
#  define SOCKET_EVENT_CONNECT 0x10
#  define SOCKET_EVENT_CLOSE   0x20
#endif // VMKERNEL
#endif // _WIN32

/*
 * Custom socket control option values.  These are internal.  The public ones
 * are in vmci_sockets.h.  As with the public options, use the address family
 * as the option level.
 */
#define SO_VMCI_EVENT_ENUMERATE_SELECT 1000

/*
 * Error codes.
 * These defines are needed for crossplatform support.
 */
#if defined(_WIN32)
#  define VSOCK_EINTR               WSAEINTR
#  define VSOCK_EACCES              WSAEACCES
#  define VSOCK_EFAULT              WSAEFAULT
#  define VSOCK_EINVAL              WSAEINVAL
#  define VSOCK_EPERM               WSAEACCES /* WSA doesn't have VSOCK_EPERM */
#  define VSOCK_ENOSYS              WSAEOPNOTSUPP
#  define VSOCK_EAGAIN              WSAEWOULDBLOCK
#  define VSOCK_EWOULDBLOCK         WSAEWOULDBLOCK
#  define VSOCK_EINPROGRESS         WSAEINPROGRESS
#  define VSOCK_EALREADY            WSAEALREADY
#  define VSOCK_ENOTSOCK            WSAENOTSOCK
#  define VSOCK_EDESTADDRREQ        WSAEDESTADDRREQ
#  define VSOCK_EMSGSIZE            WSAEMSGSIZE
#  define VSOCK_EPROTOTYPE          WSAEPROTOTYPE
#  define VSOCK_ENOPROTOOPT         WSAENOPROTOOPT
#  define VSOCK_EPROTONOSUPPORT     WSAEPROTONOSUPPORT
#  define VSOCK_EOPNOTSUPP          WSAEOPNOTSUPP
#  define VSOCK_EAFNOSUPPORT        WSAEAFNOSUPPORT
#  define VSOCK_EADDRINUSE          WSAEADDRINUSE
#  define VSOCK_EADDRNOTAVAIL       WSAEADDRNOTAVAIL
#  define VSOCK_ENETDOWN            WSAENETDOWN
#  define VSOCK_ENETUNREACH         WSAENETUNREACH
#  define VSOCK_ENETRESET           WSAENETRESET
#  define VSOCK_ECONNABORTED        WSAECONNABORTED
#  define VSOCK_ECONNRESET          WSAECONNRESET
#  define VSOCK_ENOBUFS             WSAENOBUFS
 //#  define VSOCK_ENOMEM
#  define VSOCK_EISCONN             WSAEISCONN
#  define VSOCK_ENOTCONN            WSAENOTCONN
#  define VSOCK_ETIMEDOUT           WSAETIMEDOUT
#  define VSOCK_ECONNREFUSED        WSAECONNREFUSED
#  define VSOCK_EHOSTUNREACH        WSAEHOSTUNREACH
#  define VSOCK_ESOCKTNOSUPPORT     WSAESOCKTNOSUPPORT
#  define VSOCK_EPFNOSUPPORT        WSAEPFNOSUPPORT
#  define VSOCK_ESHUTDOWN           WSAESHUTDOWN
#  define VSOCK_EHOSTDOWN           WSAEHOSTDOWN
// #  define VSOCK_EPIPE
#  define VSOCK__ELOCALSHUTDOWN     VSOCK_ESHUTDOWN
#  define VSOCK__ELOCALRCVSHUTDOWN  VSOCK__ELOCALSHUTDOWN
#  define VSOCK__EPEERSHUTDOWN      VSOCK_ECONNABORTED
#  define VSOCK__ECONNINPROGRESS    VSOCK_EWOULDBLOCK
#  define VSOCK__ESNDRCVTIMEDOUT    VSOCK_ETIMEDOUT
#  define VSOCK_ESYSNOTREADY        WSASYSNOTREADY
#elif defined(VMKERNEL)
#  define VSOCK_EINTR               VMK_WAIT_INTERRUPTED
#  define VSOCK_EACCES              VMK_NO_ACCESS
#  define VSOCK_EFAULT              VMK_INVALID_ADDRESS
#  define VSOCK_EINVAL              VMK_FAILURE
#  define VSOCK_EPERM               VMK_ACCESS_DENIED
// ENOSYS
#  define VSOCK_EAGAIN              VMK_RETRY
#  define VSOCK_EWOULDBLOCK         VMK_WOULD_BLOCK
#  define VSOCK_EINPROGRESS         VMK_EINPROGRESS
#  define VSOCK_EALREADY            VMK_EALREADY
#  define VSOCK_ENOTSOCK            VMK_NOT_A_SOCKET
#  define VSOCK_EDESTADDRREQ        VMK_EDESTADDRREQ
/*
 * Do not change VSOCK_EMSGSIZE definition without changing uses of
 * VMK_LIMIT_EXCEEDED in userSocketVmci.c's implementation of recvmsg().
 */
#  define VSOCK_EMSGSIZE            VMK_LIMIT_EXCEEDED
#  define VSOCK_EPROTOTYPE          VMK_NOT_SUPPORTED
#  define VSOCK_ENOPROTOOPT         VMK_NOT_SUPPORTED
#  define VSOCK_EPROTONOSUPPORT     VMK_EPROTONOSUPPORT
#  define VSOCK_EOPNOTSUPP          VMK_EOPNOTSUPP
#  define VSOCK_EAFNOSUPPORT        VMK_ADDRFAM_UNSUPP
#  define VSOCK_EADDRINUSE          VMK_EADDRINUSE
#  define VSOCK_EADDRNOTAVAIL       VMK_EADDRNOTAVAIL
#  define VSOCK_ENETDOWN            VMK_ENETDOWN
#  define VSOCK_ENETUNREACH         VMK_ENETUNREACH
#  define VSOCK_ENETRESET           VMK_ENETRESET
#  define VSOCK_ECONNABORTED        VMK_ECONNABORTED
#  define VSOCK_ECONNRESET          VMK_ECONNRESET
#  define VSOCK_ENOBUFS             VMK_NO_MEMORY
#  define VSOCK_ENOMEM              VMK_NO_MEMORY
#  define VSOCK_EISCONN             VMK_ALREADY_CONNECTED
#  define VSOCK_ENOTCONN            VMK_ENOTCONN
#  define VSOCK_ETIMEDOUT           VMK_TIMEOUT
#  define VSOCK_ECONNREFUSED        VMK_ECONNREFUSED
#  define VSOCK_EHOSTUNREACH        VMK_EHOSTUNREACH
#  define VSOCK_ESOCKTNOSUPPORT     VMK_NOT_SUPPORTED
#  define VSOCK_EPFNOSUPPORT        VMK_ADDRFAM_UNSUPP
#  define VSOCK_ESHUTDOWN           VMK_ESHUTDOWN
#  define VSOCK_EHOSTDOWN           VMK_EHOSTDOWN
#  define VSOCK_EPIPE               VMK_BROKEN_PIPE
#  define VSOCK__ELOCALSHUTDOWN     VSOCK_EPIPE
#  define VSOCK__ELOCALRCVSHUTDOWN  0
#  define VSOCK__EPEERSHUTDOWN      VSOCK_EPIPE
#  define VSOCK__ECONNINPROGRESS    VSOCK_EINPROGRESS
#  define VSOCK__ESNDRCVTIMEDOUT    VMK_WOULD_BLOCK
#  define VSOCK_ESYSNOTREADY        VMK_NOT_SUPPORTED
#else // Linux or Apple
#  define VSOCK_EINTR               EINTR
#  define VSOCK_EACCES              EACCES
#  define VSOCK_EFAULT              EFAULT
#  define VSOCK_EINVAL              EINVAL
#  define VSOCK_EPERM               EPERM
#  define VSOCK_ENOSYS              ENOSYS
#  define VSOCK_EAGAIN              EAGAIN
#  define VSOCK_EWOULDBLOCK         EWOULDBLOCK
#  define VSOCK_EINPROGRESS         EINPROGRESS
#  define VSOCK_EALREADY            EALREADY
#  define VSOCK_ENOTSOCK            ENOTSOCK
#  define VSOCK_EDESTADDRREQ        EDESTADDRREQ
#  define VSOCK_EMSGSIZE            EMSGSIZE
#  define VSOCK_EPROTOTYPE          EPROTOTYPE
#  define VSOCK_ENOPROTOOPT         ENOPROTOOPT
#  define VSOCK_EPROTONOSUPPORT     EPROTONOSUPPORT
#  define VSOCK_EOPNOTSUPP          EOPNOTSUPP
#  define VSOCK_EAFNOSUPPORT        EAFNOSUPPORT
#  define VSOCK_EADDRINUSE          EADDRINUSE
#  define VSOCK_EADDRNOTAVAIL       EADDRNOTAVAIL
#  define VSOCK_ENETDOWN            ENETDOWN
#  define VSOCK_ENETUNREACH         ENETUNREACH
#  define VSOCK_ENETRESET           ENETRESET
#  define VSOCK_ECONNABORTED        ECONNABORTED
#  define VSOCK_ECONNRESET          ECONNRESET
#  define VSOCK_ENOBUFS             ENOBUFS
#  define VSOCK_ENOMEM              ENOMEM
#  define VSOCK_EISCONN             EISCONN
#  define VSOCK_ENOTCONN            ENOTCONN
#  define VSOCK_ETIMEDOUT           ETIMEDOUT
#  define VSOCK_ECONNREFUSED        ECONNREFUSED
#  define VSOCK_EHOSTUNREACH        EHOSTUNREACH
#  define VSOCK_ESOCKTNOSUPPORT     ESOCKTNOSUPPORT
#  define VSOCK_EPFNOSUPPORT        EPFNOSUPPORT
#  define VSOCK_ESHUTDOWN           ESHUTDOWN
#  define VSOCK_EHOSTDOWN           EHOSTDOWN
#  define VSOCK_EPIPE               EPIPE
#endif

#if defined(__APPLE__)
#  define VSOCK__ELOCALSHUTDOWN     ESHUTDOWN
#  define VSOCK__ELOCALRCVSHUTDOWN  0
#  define VSOCK__EPEERSHUTDOWN      ECONNABORTED
#  define VSOCK__ECONNINPROGRESS    EINPROGRESS
#  define VSOCK__ESNDRCVTIMEDOUT    EAGAIN
#  define VSOCK_ESYSNOTREADY        EOPNOTSUPP
#elif defined(__linux__) && !defined(VMKERNEL)
#  define VSOCK__ELOCALSHUTDOWN     EPIPE
#  define VSOCK__ELOCALRCVSHUTDOWN  0
#  define VSOCK__EPEERSHUTDOWN      EPIPE
#  define VSOCK__ECONNINPROGRESS    EINPROGRESS
#  define VSOCK__ESNDRCVTIMEDOUT    EAGAIN
#  define VSOCK_ESYSNOTREADY        EOPNOTSUPP
#endif // _WIN32


/*
 * XXX - This is used by the vsocktest and common vsock driver code
 * but should be converted over to use the above crossplatform values
 * above. When that is completed this section can be removed!
 */
#if defined(_WIN32)

// Some defines are needed for the older SDK.
# if !defined(EINTR)
#  define EINTR               WSAEINTR
# endif
# if !defined(EACCES)
#  define EACCES              WSAEACCES
# endif
# if !defined(EFAULT)
#  define EFAULT              WSAEFAULT
# endif
# if !defined(EINVAL)
#  define EINVAL              WSAEINVAL
# endif
# if !defined(EPERM)
#  define EPERM               WSAEACCES /* WSA doesn't have EPERM */
# endif
# if !defined(ENOSYS)
#  define ENOSYS              WSAEOPNOTSUPP
# endif
# if !defined(EAGAIN)
#  define EAGAIN              WSAEWOULDBLOCK
# endif
# if !defined(EWOULDBLOCK)
#  define EWOULDBLOCK         WSAEWOULDBLOCK
#  define EINPROGRESS         WSAEINPROGRESS
#  define EALREADY            WSAEALREADY
#  define ENOTSOCK            WSAENOTSOCK
#  define EDESTADDRREQ        WSAEDESTADDRREQ
#  define EMSGSIZE            WSAEMSGSIZE
#  define EPROTOTYPE          WSAEPROTOTYPE
#  define ENOPROTOOPT         WSAENOPROTOOPT
#  define EPROTONOSUPPORT     WSAEPROTONOSUPPORT
#  define EOPNOTSUPP          WSAEOPNOTSUPP
#  define EAFNOSUPPORT        WSAEAFNOSUPPORT
#  define EADDRINUSE          WSAEADDRINUSE
#  define EADDRNOTAVAIL       WSAEADDRNOTAVAIL
#  define ENETDOWN            WSAENETDOWN
#  define ENETUNREACH         WSAENETUNREACH
#  define ENETRESET           WSAENETRESET
#  define ECONNABORTED        WSAECONNABORTED
#  define ECONNRESET          WSAECONNRESET
#  define ENOBUFS             WSAENOBUFS
#  define EISCONN             WSAEISCONN
#  define ENOTCONN            WSAENOTCONN
#  define ETIMEDOUT           WSAETIMEDOUT
#  define ECONNREFUSED        WSAECONNREFUSED
#  define EHOSTUNREACH        WSAEHOSTUNREACH
# endif
#  define ESOCKTNOSUPPORT     WSAESOCKTNOSUPPORT
#  define EPFNOSUPPORT        WSAEPFNOSUPPORT
#  define ESHUTDOWN           WSAESHUTDOWN
#  define EHOSTDOWN           WSAEHOSTDOWN
#  define __ELOCALSHUTDOWN    ESHUTDOWN
#  define __ELOCALRCVSHUTDOWN __ELOCALSHUTDOWN
#  define __EPEERSHUTDOWN     ECONNABORTED
#  define __ECONNINPROGRESS   EWOULDBLOCK
#  define __ESNDRCVTIMEDOUT   ETIMEDOUT
#  define ESYSNOTREADY        WSASYSNOTREADY
#elif defined(VMKERNEL)
#  define EINTR               VMK_WAIT_INTERRUPTED
#  define EPERM               VMK_ACCESS_DENIED
#  define EACCES              VMK_NO_ACCESS
#  define EFAULT              VMK_INVALID_ADDRESS
#  define EINVAL              VMK_FAILURE
#  define EWOULDBLOCK         VMK_WOULD_BLOCK
#  define EINPROGRESS         VMK_EINPROGRESS
#  define EALREADY            VMK_EALREADY
#  define ENOTSOCK            VMK_NOT_A_SOCKET
#  define EDESTADDRREQ        VMK_EDESTADDRREQ
   /*
    * Do not change EMSGSIZE definition without changing uses of
    * VMK_LIMIT_EXCEEDED in userSocketVmci.c's implementation of recvmsg().
    */
#  define EMSGSIZE            VMK_LIMIT_EXCEEDED
#  define EPROTOTYPE          VMK_NOT_SUPPORTED
#  define ENOPROTOOPT         VMK_NOT_SUPPORTED
#  define EPROTONOSUPPORT     VMK_EPROTONOSUPPORT
#  define ESOCKTNOSUPPORT     VMK_NOT_SUPPORTED
#  define EOPNOTSUPP          VMK_EOPNOTSUPP
#  define EPFNOSUPPORT        VMK_ADDRFAM_UNSUPP
#  define EAFNOSUPPORT        VMK_ADDRFAM_UNSUPP
#  define EADDRINUSE          VMK_EADDRINUSE
#  define EADDRNOTAVAIL       VMK_EADDRNOTAVAIL
#  define ENETDOWN            VMK_ENETDOWN
#  define ENETUNREACH         VMK_ENETUNREACH
#  define ENETRESET           VMK_ENETRESET
#  define ECONNABORTED        VMK_ECONNABORTED
#  define ECONNRESET          VMK_ECONNRESET
#  define ENOBUFS             VMK_NO_MEMORY
#  define ENOMEM              VMK_NO_MEMORY
#  define EISCONN             VMK_ALREADY_CONNECTED
#  define ENOTCONN            VMK_ENOTCONN
#  define ESHUTDOWN           VMK_ESHUTDOWN
#  define ETIMEDOUT           VMK_TIMEOUT
#  define ECONNREFUSED        VMK_ECONNREFUSED
#  define EHOSTDOWN           VMK_EHOSTDOWN
#  define EHOSTUNREACH        VMK_EHOSTUNREACH
#  define EPIPE               VMK_BROKEN_PIPE
#  define __ELOCALSHUTDOWN    EPIPE
#  define __ELOCALRCVSHUTDOWN 0
#  define __EPEERSHUTDOWN     EPIPE
#  define __ECONNINPROGRESS   EINPROGRESS
#  define __ESNDRCVTIMEDOUT   VMK_WOULD_BLOCK
#  define ESYSNOTREADY        VMK_NOT_SUPPORTED
#  define EAGAIN              VMK_RETRY
#elif defined(__APPLE__)
#  define __ELOCALSHUTDOWN    ESHUTDOWN
#  define __ELOCALRCVSHUTDOWN 0
#  define __EPEERSHUTDOWN     ECONNABORTED
#  define __ECONNINPROGRESS   EINPROGRESS
#  define __ESNDRCVTIMEDOUT   EAGAIN
#  define ESYSNOTREADY        EOPNOTSUPP
#elif defined(__linux__)
#  define ESYSNOTREADY        EOPNOTSUPP
#  define __ELOCALSHUTDOWN    EPIPE
#  define __ELOCALRCVSHUTDOWN 0
#  define __EPEERSHUTDOWN     EPIPE
#  define __ECONNINPROGRESS   EINPROGRESS
#  define __ESNDRCVTIMEDOUT   EAGAIN
#endif // _WIN32


#if defined(_WIN32)
#  define sockerr()           WSAGetLastError()
#  define sockerr2err(_e)     (((_e) < 0) ? -(_e) : (_e))
#  define sockcleanup()       WSACleanup()
   typedef uint32             socklen_t;
   typedef uint32             in_addr_t;
#else // _WIN32
#if defined(VMKERNEL)
#  define SOCKET_ERROR        (-1)
#  define INVALID_SOCKET      ((SOCKET) -1)
#  define sockerr()           errno
#  define sockerr2err(_e)     (_e)
#  define sockcleanup()       do {} while (0)
#  define closesocket(_s)     close((_s))
   typedef int32              SOCKET;
#else
#if defined(__linux__) || defined(__APPLE__)
#  define SOCKET_ERROR        (-1)
#  define INVALID_SOCKET      ((SOCKET) -1)
#  define sockerr()           errno
#  define sockcleanup()       do {} while (0)
#if defined(__linux__)
#  define sockerr2err(_e)     (((_e) > 0) ? -(_e) : (_e))
#  define closesocket(_s)     close((_s))
   typedef int32              SOCKET;
#else
#  define sockerr2err(_e)     (_e)
#  define closesocket(_s)     VMCISock_close(_s)
   typedef int32              SOCKET;
#endif
#endif // linux
#endif // VMKERNEL
#endif // _WIN32


/*
 * There is no SS_XXX state equivalent to TCP_LISTEN.  Linux does have a flag
 * __SO_ACCEPTCON which some of the socket implementations use, but it does
 * not fit in the state field (although it is sometimes incorrectly used that
 * way).  So we define our own listen state here for all platforms.
 */
#define SS_LISTEN 255


/*
 * Initialize sockets.  This is really for platforms that do not have
 * on-by-default socket implementations like Windows.
 */
int sockinit(void);


#endif // _VSOCK_SOCKET_WRAPPER_H_

