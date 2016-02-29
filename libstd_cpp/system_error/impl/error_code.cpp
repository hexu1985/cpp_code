// -*- C++ -*-
// HeXu's
// 2013 Jun

#if defined WIN32
#include <windows.h>
#include <winerror.h>
#endif

#include <cstring>
#include "error_code.h"

namespace Hx {

namespace {

class generic_error_category: public error_category {
public:
#if __cplusplus >= 201103L
	generic_error_category() = default;
#else
	generic_error_category() {}
#endif

	const char *name() const throw() { return "generic"; }

	std::string message(int val) const;
};

class system_error_category: public error_category {
public:
#if __cplusplus >= 201103L
	system_error_category() = default;
#else
	system_error_category() {}
#endif

	const char *name() const throw() { return "system"; }

	std::string message(int val) const
	{
		return generic_category().message(val);
	}

	error_condition default_error_condition(int val) const throw();
};

#if defined WIN32
std::string generic_error_category::message(int val) const
{
	switch (val) {
	case E2BIG:
		return "Argument list too long";
	case EACCES:
		return "Permission denied";
	case EADDRINUSE:
		return "Address already in use";
	case EADDRNOTAVAIL:
		return "Cannot assign requested address";
	case EAFNOSUPPORT:
		return "Address family not supported by protocol";
#if EAGAIN != EWOULDBLOCK
	case EAGAIN:
		return "Resource temporarily unavailable";
#endif
#if EALREADY != EBUSY	//  EALREADY and EBUSY are the same on QNX Neutrino
	case EALREADY:
		return "Operation already in progress";
#endif
	case EBADF:
		return "Bad file descriptor";
	case EBADMSG:
		return "Bad message";
	case EBUSY:
		return "Device or resource busy";
	case ECANCELED:
		return "Operation canceled";
	case ECHILD:
		return "No child processes";
	case ECONNABORTED:
		return "Software caused connection abort";
	case ECONNREFUSED:
		return "Connection refused";
	case ECONNRESET:
		return "Connection reset by peer";
	case EDEADLK:
		return "Resource deadlock avoided";
	case EDESTADDRREQ:
		return "Destination address required";
	case EDOM:
		return "Numerical argument out of domain";
	case EEXIST:
		return "File exists";
	case EFAULT:
		return "Bad address";
	case EFBIG:
		return "File too large";
	case EHOSTDOWN:
		return "Host is down";
	case EHOSTUNREACH:
		return "No route to host";
	case EIDRM:
		return "Identifier removed";
	case EILSEQ:
		return "Invalid or incomplete multibyte or wide character";
	case EINPROGRESS:
		return "Operation now in progress";
	case EINTR:
		return "Interrupted system call";
	case EINVAL:
		return "Invalid argument";
	case EIO:
		return "Input/output error";
	case EISCONN:
		return "Transport endpoint is already connected";
	case EISDIR:
		return "Is a directory";
	case ELOOP:
		return "Too many levels of symbolic links";
	case EMFILE:
		return "Too many open files";
	case EMLINK:
		return "Too many links";
	case EMSGSIZE:
		return "Message too long";
	case ENAMETOOLONG:
		return "File name too long";
	case ENETDOWN:
		return "Network is down";
	case ENETRESET:
		return "Network dropped connection on reset";
	case ENETUNREACH:
		return "Network is unreachable";
	case ENFILE:
		return "Too many open files in system";
	case ENOBUFS:
		return "No buffer space available";
	case ENODATA:
		return "No data available";
	case ENODEV:
		return "No such device";
	case ENOENT:
		return "No such file or directory";
	case ENOEXEC:
		return "Exec format error";
	case ENOLCK:
		return "No locks available";
	case ENOLINK:
		return "Link has been severed";
	case ENOMEM:
		return "Cannot allocate memory";
	case ENOMSG:
		return "No message of desired type";
	case ENOPROTOOPT:
		return "Protocol not available";
	case ENOSPC:
		return "No space left on device";
	case ENOSR:
		return "Out of streams resources";
	case ENOSTR:
		return "Device not a stream";
	case ENOSYS:
		return "Function not implemented";
	case ENOTCONN:
		return "Transport endpoint is not connected";
	case ENOTDIR:
		return "Not a directory";
#if ENOTEMPTY != EEXIST	// AIX treats ENOTEMPTY and EEXIST as the same value
	case ENOTEMPTY:
		return "Directory not empty";
#endif
#if ENOTRECOVERABLE != ECONNRESET	// the same on some Broadcom chips 
	case ENOTRECOVERABLE:
		return "State not recoverable";
#endif
	case ENOTSOCK:
		return "Socket operation on non-socket";
	case ENOTSUP:
		return "Operation not supported";
	case ENOTTY:
		return "Inappropriate ioctl for device";
	case ENXIO:
		return "No such device or address";
#if EOPNOTSUPP != ENOTSUP
	case EOPNOTSUPP:
		return "Operation not supported";
#endif
	case EOVERFLOW:
		return "Value too large for defined data type";
#if EOWNERDEAD != ECONNABORTED // the same on some Broadcom chips 
	case EOWNERDEAD:
		return "Owner died";
#endif
	case EPERM:
		return "Operation not permitted";
	case EPFNOSUPPORT:
		return "Protocol family not supported";
	case EPIPE:
		return "Broken pipe";
	case EPROTO:
		return "Protocol error";
	case EPROTONOSUPPORT:
		return "Protocol not supported";
	case EPROTOTYPE:
		return "Protocol wrong type for socket";
	case ERANGE:
		return "Numerical result out of range";
	case EROFS:
		return "Read-only file system";
	case ESHUTDOWN:
		return "Cannot send after transport endpoint shutdown";
	case ESOCKTNOSUPPORT:
		return "Socket type not supported";
	case ESPIPE:
		return "Illegal seek";
	case ESRCH:
		return "No such process";
	case ETIME:
		return "Timer expired";
	case ETIMEDOUT:
		return "Connection timed out";
	case ETOOMANYREFS:
		return "Too many references: cannot splice";
	case ETXTBSY:
		return "Text file busy";
	case EWOULDBLOCK:
		return "Resource temporarily unavailable";
	case EXDEV:
		return "Invalid cross-device link";
	default:
		break;
	} 
	
	HLOCAL hlocal = NULL;
	FormatMessage(
		FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER, NULL, 
		val, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
		(LPTSTR) &hlocal, 0, NULL);
	if (hlocal != NULL) {
		std::string msg((const char *)hlocal);
		LocalFree(hlocal);
#if __cplusplus >= 201103L
		return std::move(msg);
#else
		return msg;
#endif
	}

	return std::strerror(val);
}
#else
std::string generic_error_category::message(int val) const
{
	return std::strerror(val);
}
#endif

error_condition system_error_category::default_error_condition(int val) 
	const throw()
{
	switch (val) {
	case 0: return make_error_condition(errc::success);
#if !defined WIN32
	// POSIX-like O/S -> posix_errno decode table  ---------------------------//
	case E2BIG: return make_error_condition(errc::argument_list_too_long);
	case EACCES: return make_error_condition(errc::permission_denied);
	case EADDRINUSE: return make_error_condition(errc::address_in_use);
	case EADDRNOTAVAIL: return make_error_condition(errc::address_not_available);
	case EAFNOSUPPORT: return make_error_condition(errc::address_family_not_supported);
	case EAGAIN: return make_error_condition(errc::resource_unavailable_try_again);
#if EALREADY != EBUSY  //  EALREADY and EBUSY are the same on QNX Neutrino
	case EALREADY: return make_error_condition(errc::connection_already_in_progress);
#endif
	case EBADF: return make_error_condition(errc::bad_file_descriptor);
	case EBADMSG: return make_error_condition(errc::bad_message);
	case EBUSY: return make_error_condition(errc::device_or_resource_busy);
	case ECANCELED: return make_error_condition(errc::operation_canceled);
	case ECHILD: return make_error_condition(errc::no_child_process);
	case ECONNABORTED: return make_error_condition(errc::connection_aborted);
	case ECONNREFUSED: return make_error_condition(errc::connection_refused);
	case ECONNRESET: return make_error_condition(errc::connection_reset);
	case EDEADLK: return make_error_condition(errc::resource_deadlock_would_occur);
	case EDESTADDRREQ: return make_error_condition(errc::destination_address_required);
	case EDOM: return make_error_condition(errc::argument_out_of_domain);
	case EEXIST: return make_error_condition(errc::file_exists);
	case EFAULT: return make_error_condition(errc::bad_address);
	case EFBIG: return make_error_condition(errc::file_too_large);
	case EHOSTUNREACH: return make_error_condition(errc::host_unreachable);
	case EIDRM: return make_error_condition(errc::identifier_removed);
	case EILSEQ: return make_error_condition(errc::illegal_byte_sequence);
	case EINPROGRESS: return make_error_condition(errc::operation_in_progress);
	case EINTR: return make_error_condition(errc::interrupted);
	case EINVAL: return make_error_condition(errc::invalid_argument);
	case EIO: return make_error_condition(errc::io_error);
	case EISCONN: return make_error_condition(errc::already_connected);
	case EISDIR: return make_error_condition(errc::is_a_directory);
	case ELOOP: return make_error_condition(errc::too_many_symbolic_link_levels);
	case EMFILE: return make_error_condition(errc::too_many_files_open);
	case EMLINK: return make_error_condition(errc::too_many_links);
	case EMSGSIZE: return make_error_condition(errc::message_size);
	case ENAMETOOLONG: return make_error_condition(errc::filename_too_long);
	case ENETDOWN: return make_error_condition(errc::network_down);
	case ENETRESET: return make_error_condition(errc::network_reset);
	case ENETUNREACH: return make_error_condition(errc::network_unreachable);
	case ENFILE: return make_error_condition(errc::too_many_files_open_in_system);
	case ENOBUFS: return make_error_condition(errc::no_buffer_space);
	case ENODATA: return make_error_condition(errc::no_message_available);
	case ENODEV: return make_error_condition(errc::no_such_device);
	case ENOENT: return make_error_condition(errc::no_such_file_or_directory);
	case ENOEXEC: return make_error_condition(errc::executable_format_error);
	case ENOLCK: return make_error_condition(errc::no_lock_available);
	case ENOLINK: return make_error_condition(errc::no_link);
	case ENOMEM: return make_error_condition(errc::not_enough_memory);
	case ENOMSG: return make_error_condition(errc::no_message);
	case ENOPROTOOPT: return make_error_condition(errc::no_protocol_option);
	case ENOSPC: return make_error_condition(errc::no_space_on_device);
	case ENOSR: return make_error_condition(errc::no_stream_resources);
	case ENOSTR: return make_error_condition(errc::not_a_stream);
	case ENOSYS: return make_error_condition(errc::function_not_supported);
	case ENOTCONN: return make_error_condition(errc::not_connected);
	case ENOTDIR: return make_error_condition(errc::not_a_directory);
#if ENOTEMPTY != EEXIST // AIX treats ENOTEMPTY and EEXIST as the same value
	case ENOTEMPTY: return make_error_condition(errc::directory_not_empty);
#endif // ENOTEMPTY != EEXIST
#if ENOTRECOVERABLE != ECONNRESET // the same on some Broadcom chips 
	case ENOTRECOVERABLE: return make_error_condition(errc::state_not_recoverable); 
#endif // ENOTRECOVERABLE != ECONNRESET 
	case ENOTSOCK: return make_error_condition(errc::not_a_socket);
	case ENOTSUP: return make_error_condition(errc::not_supported);
	case ENOTTY: return make_error_condition(errc::inappropriate_io_control_operation);
	case ENXIO: return make_error_condition(errc::no_such_device_or_address);
#if EOPNOTSUPP != ENOTSUP
	case EOPNOTSUPP: return make_error_condition(errc::operation_not_supported);
#endif // EOPNOTSUPP != ENOTSUP
	case EOVERFLOW: return make_error_condition(errc::value_too_large);
#if EOWNERDEAD != ECONNABORTED // the same on some Broadcom chips 
	case EOWNERDEAD: return make_error_condition(errc::owner_dead); 
#endif // EOWNERDEAD != ECONNABORTED 
	case EPERM: return make_error_condition(errc::operation_not_permitted);
	case EPIPE: return make_error_condition(errc::broken_pipe);
	case EPROTO: return make_error_condition(errc::protocol_error);
	case EPROTONOSUPPORT: return make_error_condition(errc::protocol_not_supported);
	case EPROTOTYPE: return make_error_condition(errc::wrong_protocol_type);
	case ERANGE: return make_error_condition(errc::result_out_of_range);
	case EROFS: return make_error_condition(errc::read_only_file_system);
	case ESPIPE: return make_error_condition(errc::invalid_seek);
	case ESRCH: return make_error_condition(errc::no_such_process);
	case ETIME: return make_error_condition(errc::stream_timeout);
	case ETIMEDOUT: return make_error_condition(errc::timed_out);
	case ETXTBSY: return make_error_condition(errc::text_file_busy);
#if EAGAIN != EWOULDBLOCK
	case EWOULDBLOCK: return make_error_condition(errc::operation_would_block);
#endif // EAGAIN != EWOULDBLOCK
	case EXDEV: return make_error_condition(errc::cross_device_link);
#else
	// Windows system -> posix_errno decode table  ---------------------------//
	// see WinError.h comments for descriptions of errors
	case ERROR_ACCESS_DENIED: return make_error_condition(errc::permission_denied);
	case ERROR_ALREADY_EXISTS: return make_error_condition(errc::file_exists);
	case ERROR_BAD_UNIT: return make_error_condition(errc::no_such_device);
	case ERROR_BUFFER_OVERFLOW: return make_error_condition(errc::filename_too_long);
	case ERROR_BUSY: return make_error_condition(errc::device_or_resource_busy);
	case ERROR_BUSY_DRIVE: return make_error_condition(errc::device_or_resource_busy);
	case ERROR_CANNOT_MAKE: return make_error_condition(errc::permission_denied);
	case ERROR_CANTOPEN: return make_error_condition(errc::io_error);
	case ERROR_CANTREAD: return make_error_condition(errc::io_error);
	case ERROR_CANTWRITE: return make_error_condition(errc::io_error);
	case ERROR_CURRENT_DIRECTORY: return make_error_condition(errc::permission_denied);
	case ERROR_DEV_NOT_EXIST: return make_error_condition(errc::no_such_device);
	case ERROR_DEVICE_IN_USE: return make_error_condition(errc::device_or_resource_busy);
	case ERROR_DIR_NOT_EMPTY: return make_error_condition(errc::directory_not_empty);
	case ERROR_DIRECTORY: return make_error_condition(errc::invalid_argument); // WinError.h: "The directory name is invalid"
	case ERROR_DISK_FULL: return make_error_condition(errc::no_space_on_device);
	case ERROR_FILE_EXISTS: return make_error_condition(errc::file_exists);
	case ERROR_FILE_NOT_FOUND: return make_error_condition(errc::no_such_file_or_directory);
	case ERROR_HANDLE_DISK_FULL: return make_error_condition(errc::no_space_on_device);
	case ERROR_INVALID_ACCESS: return make_error_condition(errc::permission_denied);
	case ERROR_INVALID_DRIVE: return make_error_condition(errc::no_such_device);
	case ERROR_INVALID_FUNCTION: return make_error_condition(errc::function_not_supported);
	case ERROR_INVALID_HANDLE: return make_error_condition(errc::invalid_argument);
	case ERROR_INVALID_NAME: return make_error_condition(errc::invalid_argument);
	case ERROR_LOCK_VIOLATION: return make_error_condition(errc::no_lock_available);
	case ERROR_LOCKED: return make_error_condition(errc::no_lock_available);
	case ERROR_NEGATIVE_SEEK: return make_error_condition(errc::invalid_argument);
	case ERROR_NOACCESS: return make_error_condition(errc::permission_denied);
	case ERROR_NOT_ENOUGH_MEMORY: return make_error_condition(errc::not_enough_memory);
	case ERROR_NOT_READY: return make_error_condition(errc::resource_unavailable_try_again);
	case ERROR_NOT_SAME_DEVICE: return make_error_condition(errc::cross_device_link);
	case ERROR_OPEN_FAILED: return make_error_condition(errc::io_error);
	case ERROR_OPEN_FILES: return make_error_condition(errc::device_or_resource_busy);
	case ERROR_OPERATION_ABORTED: return make_error_condition(errc::operation_canceled);
	case ERROR_OUTOFMEMORY: return make_error_condition(errc::not_enough_memory);
	case ERROR_PATH_NOT_FOUND: return make_error_condition(errc::no_such_file_or_directory);
	case ERROR_READ_FAULT: return make_error_condition(errc::io_error);
	case ERROR_RETRY: return make_error_condition(errc::resource_unavailable_try_again);
	case ERROR_SEEK: return make_error_condition(errc::io_error);
	case ERROR_SHARING_VIOLATION: return make_error_condition(errc::permission_denied);
	case ERROR_TOO_MANY_OPEN_FILES: return make_error_condition(errc::too_many_files_open);
	case ERROR_WRITE_FAULT: return make_error_condition(errc::io_error);
	case ERROR_WRITE_PROTECT: return make_error_condition(errc::permission_denied);
	case WSAEACCES: return make_error_condition(errc::permission_denied);
	case WSAEADDRINUSE: return make_error_condition(errc::address_in_use);
	case WSAEADDRNOTAVAIL: return make_error_condition(errc::address_not_available);
	case WSAEAFNOSUPPORT: return make_error_condition(errc::address_family_not_supported);
	case WSAEALREADY: return make_error_condition(errc::connection_already_in_progress);
	case WSAEBADF: return make_error_condition(errc::bad_file_descriptor);
	case WSAECONNABORTED: return make_error_condition(errc::connection_aborted);
	case WSAECONNREFUSED: return make_error_condition(errc::connection_refused);
	case WSAECONNRESET: return make_error_condition(errc::connection_reset);
	case WSAEDESTADDRREQ: return make_error_condition(errc::destination_address_required);
	case WSAEFAULT: return make_error_condition(errc::bad_address);
	case WSAEHOSTUNREACH: return make_error_condition(errc::host_unreachable);
	case WSAEINPROGRESS: return make_error_condition(errc::operation_in_progress);
	case WSAEINTR: return make_error_condition(errc::interrupted);
	case WSAEINVAL: return make_error_condition(errc::invalid_argument);
	case WSAEISCONN: return make_error_condition(errc::already_connected);
	case WSAEMFILE: return make_error_condition(errc::too_many_files_open);
	case WSAEMSGSIZE: return make_error_condition(errc::message_size);
	case WSAENAMETOOLONG: return make_error_condition(errc::filename_too_long);
	case WSAENETDOWN: return make_error_condition(errc::network_down);
	case WSAENETRESET: return make_error_condition(errc::network_reset);
	case WSAENETUNREACH: return make_error_condition(errc::network_unreachable);
	case WSAENOBUFS: return make_error_condition(errc::no_buffer_space);
	case WSAENOPROTOOPT: return make_error_condition(errc::no_protocol_option);
	case WSAENOTCONN: return make_error_condition(errc::not_connected);
	case WSAENOTSOCK: return make_error_condition(errc::not_a_socket);
	case WSAEOPNOTSUPP: return make_error_condition(errc::operation_not_supported);
	case WSAEPROTONOSUPPORT: return make_error_condition(errc::protocol_not_supported);
	case WSAEPROTOTYPE: return make_error_condition(errc::wrong_protocol_type);
	case WSAETIMEDOUT: return make_error_condition(errc::timed_out);
	case WSAEWOULDBLOCK: return make_error_condition(errc::operation_would_block);
#endif
	default: return error_condition(val, system_category());
	}
}

}	// namespace

const error_category &generic_category() throw()
{
	static const generic_error_category generic_category_;
	return generic_category_;
}

const error_category &system_category() throw()
{
	static const system_error_category system_category_;
	return system_category_;
}

}	// namespace Hx


