
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
	start();
private:
	void
	do_run();

	std::vector<shared_ptr<UPDATE_COMP_T>> event_listeners;
	std::thread time_thread;
};

class i_event_listener
{
public:
	/*
	 * A class which is derived from, either directly or
	 * indirectly, the event listener interface (i_event_listener)
	 * must provide a definition for the callback function
	 * `do_update`.
	 * 
	 * `do_update` is called by the update handler, which itself
	 * registers the components in our system which have state that
	 * may regularly change. These changes to state happen in their
	 * implementation of this function. 
	 * 
	 * A function which is dependent on time can use the double 
	 * parameter passed by the update handler, which is a time 
	 * delta; that is to say, the difference between the time
	 * of this function call and the last.
	 */
	virtual void
	do_update(double time_delta)=0;
};

extern template class update_handle<i_event_listener>;

/* 
 * class game_char : ..., i_event_listener
 * {
 * private:
 *   int x, y;
 *   unique_ptr<png_image> img;
 * public:
 *   void
 *   do_update(double time_delta) override
 *   {
 *     x=y*time_delta+x;
 *   }
 * }
 */
#endif /* time_hpp */
