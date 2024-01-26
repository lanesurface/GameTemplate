
#include <chrono>
#include <memory>
#include <initializer_list>

#ifndef time_hpp
#define time_hpp

using std::unique_ptr, std::shared_ptr;

static class time_keeper_T
{
	typedef long long int time_T;
	
	time_T curr_time_ns, last_time_ns;
	int req_ticks_per_s;
	
public:
	time_keeper_T()=delete;
	
	explicit
	time_keeper_T(int t) : req_ticks_per_s(t) {}
	
	[[no_discard]]
	inline time_T
	get_time_ms();
	
	[[no_discard]]
	inline time_T
	get_last_time_ms();
};

template <typename UPDATE_COMP_T>
class update_handle
{
	friend class UPDATE_COMP_T;
public:
	void
	register_event_listeners(std::initializer_list<UPDATE_COMP_T>);
	
	void
	do_run();
private:
	std::vector<shared_ptr<UPDATE_COMP_T>> event_listeners;
	std::thread time_thread;
};

#endif /* time_hpp */
