# json-match-asio
## Motivation
What if asio-tcp read  pure json without using splices or [net string](https://en.wikipedia.org/wiki/Netstring)?
## How to use
    ...
    void handler(const boost::system::error_code& e, std::size_t size);
    ...
    boost::asio::streambuf b;
    boost::asio::async_read_until(s, b, JsonMatch{}, handler);