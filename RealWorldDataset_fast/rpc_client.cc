#include "DistSSE.client.h"
#include "DistSSE.db_generator.h"

#include "logger.h"

using DistSSE::SearchRequestMessage;


void split(const std::string &s, std::vector <std::string> &sv, const char flag = ' ') {
    sv.clear();
    std::istringstream iss(s);
    std::string temp;

    while (std::getline(iss, temp, flag)) {
        sv.push_back(temp);
    }
    return;
}

void update(DistSSE::Client &client, std::string key_value_dbPath) {
    rocksdb::DB *ss_db;
    rocksdb::Options options;
    options.create_if_missing = true;
    options.merge_operator.reset(new rocksdb::StringAppendOperator());
    options.use_fsync = true;
    rocksdb::Status s1 = rocksdb::DB::Open(options, key_value_dbPath, &ss_db);
    if (!s1.ok()) {
        std::cerr << "open ssdb error:" << s1.ToString() << std::endl;
    }
    rocksdb::Iterator *it = ss_db->NewIterator(rocksdb::ReadOptions());
    std::string filename;
    std::string value;
    int count = 0;

    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    std::cout << "asdasd..." << std::endl;


    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        if (count == 10) {
            gettimeofday(&t2, NULL);
            double update_time = ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0;
            DistSSE::logger::log_benchmark() << "update(ms): " << count << " " << update_time << std::endl;
        }
        if (count == 100) {
            gettimeofday(&t2, NULL);
            double update_time = ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0;
            DistSSE::logger::log_benchmark() << "update(ms): " << count << " " << update_time << std::endl;
        }
        if (count == 1000) {
            gettimeofday(&t2, NULL);
            double update_time = ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0;
            DistSSE::logger::log_benchmark() << "update(ms): " << count << " " << update_time << std::endl;
        }
        if (count == 10000) {
            gettimeofday(&t2, NULL);
            double update_time = ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0;
            DistSSE::logger::log_benchmark() << "update(ms): " << count << " " << update_time << std::endl;
        }
        if (count == 100000) {
            gettimeofday(&t2, NULL);
            double update_time = ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0;
            DistSSE::logger::log_benchmark() << "update(ms): " << count << " " << update_time << std::endl;
            break;
        }
        filename = it->key().ToString();
        value = it->value().ToString();

        std::vector <std::string> keywords;
        split(value, keywords, ',');
        for (const auto &keyword : keywords) {
            //std::cout << filename + " " + keyword << std::endl;
            client.update("1", keyword, filename);
        }
        count++;
    }
    delete it;
}

int main(int argc, char **argv) {
    DistSSE::logger::set_severity(DistSSE::logger::INFO);
    //DistSSE::logger::log(DistSSE::logger::INFO) << " client test :  "<< std::endl;
    //DistSSE::logger::log_benchmark() << "client to file" <<std::endl;
    // Instantiate the client and channel isn't authenticated
    DistSSE::Client client(grpc::CreateChannel("0.0.0.0:50051", grpc::InsecureChannelCredentials()),
                           std::string(argv[1]));

    if (argc < 7) {
        std::cerr << "argc error" << std::endl;
        exit(-1);
    }

    size_t N_entry = atoi(argv[2]);
    std::string w = std::string(argv[3]);
    int flag = atoi(argv[4]);
    int threads_num = atoi(argv[5]);
    std::cout << "update begin..." << std::endl;


    //if (flag == 1) DistSSE::generate_trace(&client, N_entry);
    if (flag == 1) {
        DistSSE::gen_db(client, N_entry, threads_num);
        std::cout << "update done." << std::endl;
        client.search(w);
        std::cout << "search done: " << std::endl;
    } else if (flag == 2) {
        std::string logFileName = argv[6];
        DistSSE::logger::set_benchmark_file(logFileName);
        DistSSE::gen_db_2(client, N_entry, w, threads_num);
        std::cout << "update done." << std::endl;
    } else if (flag == 3) {
        client.search(w);
        std::cout << "search done: " << std::endl;
    } else if (flag == 4) {
        std::string logFileName = argv[6];
        DistSSE::logger::set_benchmark_file(logFileName);
        DistSSE::gen_db_4(client, N_entry, threads_num);
        std::cout << "update done." << std::endl;
    } else if (flag == 5) {
        rocksdb::DB *ss_db;
        rocksdb::Options options;
        options.create_if_missing = true;
        options.merge_operator.reset(new rocksdb::StringAppendOperator());
        options.use_fsync = true;
        rocksdb::Status s1 = rocksdb::DB::Open(options, key_value_dbPath, &ss_db);
        if (!s1.ok()) {
            std::cerr << "open ssdb error:" << s1.ToString() << std::endl;
        }
        rocksdb::Iterator *it = ss_db->NewIterator(rocksdb::ReadOptions());
        std::string filename;
        std::string value;
        int count = 0;

        struct timeval t1, t2;
        gettimeofday(&t1, NULL);
        std::cout << "asdasd..." << std::endl;


        for (it->SeekToFirst(); it->Valid(); it->Next()) {
            if (count == 10) {
                gettimeofday(&t2, NULL);
                double update_time = ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0;
                DistSSE::logger::log_benchmark() << "update(ms): " << count << " " << update_time << std::endl;
            }
            if (count == 100) {
                gettimeofday(&t2, NULL);
                double update_time = ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0;
                DistSSE::logger::log_benchmark() << "update(ms): " << count << " " << update_time << std::endl;
            }
            if (count == 1000) {
                gettimeofday(&t2, NULL);
                double update_time = ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0;
                DistSSE::logger::log_benchmark() << "update(ms): " << count << " " << update_time << std::endl;
            }
            if (count == 10000) {
                gettimeofday(&t2, NULL);
                double update_time = ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0;
                DistSSE::logger::log_benchmark() << "update(ms): " << count << " " << update_time << std::endl;
            }
            if (count == 100000) {
                gettimeofday(&t2, NULL);
                double update_time = ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0;
                DistSSE::logger::log_benchmark() << "update(ms): " << count << " " << update_time << std::endl;
                break;
            }
            filename = it->key().ToString();
            value = it->value().ToString();

            std::vector <std::string> keywords;
            split(value, keywords, ',');
            for (const auto &keyword : keywords) {
                //std::cout << filename + " " + keyword << std::endl;
                client.update("1", keyword, filename);
            }
            count++;
        }
        delete it;
    } else {

    }
    return 0;
}

