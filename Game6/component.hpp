class Component {
	bool active;
public:
	virtual void reset() = 0;
	Component() : active(false){}
};