enum class Error {
    NoError,
    CorruptedArchive
};

class Serializer {
    static const char sep = ' ';
public:
    explicit Serializer(std::ostream& out_)
        : out(out_) { }

    template <class T>
    Error save(T& object) {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT... args) {
        return process(args...);
    }
    
private:
	std::ostream& out;

	Error process(bool val) {
	    if (val)
	    	out << "true" << sep;
	    else
	    	out << "false" << sep;
	    return Error::NoError;
	}

	Error process(uint64_t val) {
	    out << val << sep;
	    return Error::NoError;
	}
    
	template <class T, class... ArgsT>
	Error process(T& val, ArgsT&... args) {
	    process(val);
	    return process(std::forward<ArgsT&>(args)...);
	}
};

class Deserializer {
public:
    explicit Deserializer(std::istream& in_)
        : in(in_) { }

    template <class T>
    Error load(T& object) {
        return object.serialize(*this);
    }

    template <class... ArgsT>
    Error operator()(ArgsT&... args) {
        return process(args...);
    }
    
private:
	std::istream& in;

	Error process(bool& val) {
	    std::string text;
	    in >> text;

	    if (text == "true")
	        val = true;
	    else if (text == "false")
	        val = false;
	    else
	        return Error::CorruptedArchive;

	    return Error::NoError;
	}

	Error process(uint64_t& val) {
	    if (in >> val)
	    	return Error::NoError;
	    else
	    	return Error::CorruptedArchive;
	}
    
	template <class T, class... ArgsT>
	Error process(T& val, ArgsT&... args) {
	    Error err = process(val);
	    if (err == Error::NoError)
	    	return process(std::forward<ArgsT&>(args)...);
	    else
	    	return Error::CorruptedArchive;
	}
};