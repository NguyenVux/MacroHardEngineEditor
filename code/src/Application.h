class Application {
protected:
	struct AccessKey;
private:
	//fteng::connection onUpdateConnection;
	//MHTL::public_signal_t<void(float i_delta), AccessKey> sig_onApplicationUpdate;
	//std::unique_ptr<IDisplay> display;
public:
	Application();
	void Update(float i_delta);

	~Application();
};
