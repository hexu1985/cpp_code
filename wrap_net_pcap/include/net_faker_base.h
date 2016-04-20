#ifndef	NET_FACKER_BASE_H
#define	NET_FACKER_BASE_H

#include <libnet.h>

// 网络报文伪造器
class Net_faker_base {
private:
	libnet_t *m_handle;		// libnet handle

public:
	Net_faker_base();
	Net_faker_base(const char *device, int injection_type = LIBNET_LINK);

	~Net_faker_base();

	// 打开报文伪造器, device为设备名
	void open(const char *device, int injection_type = LIBNET_LINK);

	// 伪造器是否打开
	bool is_open() const;

	// 关闭伪造器
	void close();

public:
	// 获取native handle
	typedef libnet_t *native_handle_type;
	native_handle_type native_handle() { return m_handle; }

	// 释放native handle
	native_handle_type release();

	// reset native handle
	void reset(native_handle_type handle = NULL);

private:
	// 初始化函数
	void init();

private:
	// delete operator
	Net_faker_base(const Net_faker_base &);
	Net_faker_base &operator =(const Net_faker_base &);
};

#endif
