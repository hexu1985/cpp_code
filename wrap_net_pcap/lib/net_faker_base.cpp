#include "net_faker_base.h"
#include "wraplibnet.h"
#include <stdexcept>

using std::runtime_error;

void Net_faker_base::init()
{
	m_handle = NULL;
}

Net_faker_base::Net_faker_base()
{
	init();
}

Net_faker_base::Net_faker_base(const char *device, int injection_type)
{
	init();
	open(device, injection_type);
}

Net_faker_base::~Net_faker_base()
{
	close();
}

void Net_faker_base::open(const char *device, int injection_type)
{
	// 不能重复open
	if (is_open()) {
		throw runtime_error("Net_faker_base::open error: already opened!");
	}

	// open device
	reset(Libnet_init(injection_type, (char *) device));
}

bool Net_faker_base::is_open() const
{
	return m_handle != NULL;
}

void Net_faker_base::close()
{
	reset();
}

Net_faker_base::native_handle_type Net_faker_base::release()
{
	native_handle_type tmp = m_handle;
	reset();
	return tmp;
}

void Net_faker_base::reset(native_handle_type handle)
{
	// close当前handle
	if (m_handle != NULL) {
		libnet_destroy(m_handle);
	}

	// 设置handle和datalink type
	m_handle = handle;
}

