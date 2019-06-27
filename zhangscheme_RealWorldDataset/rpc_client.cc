#include "DistSSE.client.h"
#include "DistSSE.db_generator.h"

#include "logger.h"
#include <vector>

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

void update(DistSSE::Client &client, std::string key_value_dbPath, int maxNum) {
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
        }

        if(count>maxNum){
            // end the process of evaluation
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
    // argv[1] path of database; argv[2] path of key_value database; argv[3] path of
    std::string dbPath = std::string(argv[2]);
    DistSSE::Client client(grpc::CreateChannel("0.0.0.0:50051", grpc::InsecureChannelCredentials()),
                           dbPath);

    int type = atoi(argv[1]);
    if (type == 1) {
        DistSSE::logger::set_benchmark_file(argv[4]);
        std::cout << "update..." << std::endl;
        int maxNum = std::atoi(argv[5]);
        std::string key_value_dbPath = std::string(argv[3]);
        update(client, key_value_dbPath, maxNum);
    } else if (type == 2) {
        std::cout << "search..." << std::endl;
        std::string keyword = std::string(argv[3]);
        std::cout << keyword << std::endl;
        client.search(keyword);
    } else if(type == 3){
         DistSSE::logger::set_benchmark_file(argv[4]);
         std::cout << "search..." << std::endl;
         std::string keyword = std::string(argv[3]);
         std::cout << keyword << std::endl;
         client.search2(keyword);
    }
    return 0;
}

