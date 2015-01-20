typedef shared_ptr<google::protobuf::Message> MessagePtr;

class MessageHandler
{
public:
    virtual ~MessageHandler() {};
    virtual std::string on_key(const MessagePtr &message) const = 0;
};

template <typename T>
class MessageHandlerT : public MessageHandler
{
public:
    typedef boost::function<std::string (const boost::shared_ptr<T> &)> MessageCallBack;
private:
    MessageCallBack m_cb;
public:
    MessageHandlerT(const MessageCallBack &callback):
        m_cb(callback)
    {
    }

    virtual std::string on_key(const MessagePtr &message) const
    {
        return m_cb(message);
    }
    virtual ~MessageHandlerT()
    {}
};

class KeyGenerator
{
pubilic:
    typedef boost::function<std::string (const MessagePtr &message)> MessageCallBack;
private:
    typedef std::map<google::protobuf::Descriptor *, boost::shared_ptr<MessageHandler> > MessageHandlerMap;
    MessageHandlerMap m_callbacks;
    MessageCallBack m_default_cb;
public:
    KeyGenerator(const MessageCallBack &default_cb):
        m_default_cb(default_cb)
    {
    }

    template <typename T>
    void register_handler(const typename MessageHandlerT<T>::MessageCallBack &callback)
    {
        boost::shared_ptr<MessageHandlerT<T> > message_handler(new MessageHandlerT<T>(callback));
        m_callbacks[T::descriptor()] = message_handler;
    }

    std::string on_key(const MessagePtr &message)
    {
        MessageHandlerMap::const_iterator itr = m_callbacks.find(message->GetDescriptor());
        if (itr != m_callbacks.end()) {
            itr->second->on_key(message);
        } else {
            m_default_cb(message);
        }
    }
};


