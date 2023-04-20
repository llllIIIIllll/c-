
```c++

    // 多线程创建异步并行任务
    std::vector<std::future<void>> m_vctFut;

    // auto start = std::chrono::high_resolution_clock::now();


    for (auto& remote : _remotes) {
        // threads.push_back(std::thread(&UdpConnection::send_handle, this, message, remote.ip, remote.port_number));
        // 多线程创建异步并行任务
        auto func = std::bind(&UdpConnection::send_handle, this, message, remote.ip, remote.port_number);
        std::future<void> fut = std::async(std::launch::async, func);
        m_vctFut.push_back(std::move(fut));

        // send_handle(message, remote.ip, remote.port_number);
    }
```