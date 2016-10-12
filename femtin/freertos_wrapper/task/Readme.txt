1/

class MyTask : public Task
{
public:
	virtual void run()
	{
		// my task implementation
	}	
}

2/

voif f(void)
{
	Task mytask(g, arg);
	mytask.join();
}

Problem:

void c_register(void(*pf)(void*), void* arg);

