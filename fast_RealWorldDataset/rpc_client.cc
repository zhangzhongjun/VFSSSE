#include "DistSSE.client.h"
#include "DistSSE.db_generator.h"

#include "logger.h"
#include "DistSSE.Util.h"
#include <cmath>
#include <chrono>


using DistSSE::SearchRequestMessage;
using DistSSE::UpdateRequestMessage;
using DistSSE::ExecuteStatus;
using DistSSE::RPC;


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

    // for gRPC
    UpdateRequestMessage request;
    ClientContext context;
    ExecuteStatus exec_status;
    std::unique_ptr <RPC::Stub> stub_(RPC::NewStub(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials())));
    std::unique_ptr <ClientWriterInterface<UpdateRequestMessage>> writer(stub_->batch_update(&context, &exec_status));

    struct timeval t1, t2;
    gettimeofday(&t1, NULL);


    std::cout << maxNum << std::endl;


    for (it->SeekToFirst(); it->Valid(); it->Next()) {
        if (count == 32768) {
            gettimeofday(&t2, NULL);
            double update_time = ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0;
            DistSSE::logger::log_benchmark() << "update(ms): " << count << " " << update_time << std::endl;
        }
        if (count == 65536) {
            gettimeofday(&t2, NULL);
            double update_time = ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0;
            DistSSE::logger::log_benchmark() << "update(ms): " << count << " " << update_time << std::endl;
        }
        if (count == 131072) {
            gettimeofday(&t2, NULL);
            double update_time = ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0;
            DistSSE::logger::log_benchmark() << "update(ms): " << count << " " << update_time << std::endl;
        }
        if (count == 262144) {
            gettimeofday(&t2, NULL);
            double update_time = ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0;
            DistSSE::logger::log_benchmark() << "update(ms): " << count << " " << update_time << std::endl;
        }
        if (count == 524288) {
            gettimeofday(&t2, NULL);
            double update_time = ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0;
            DistSSE::logger::log_benchmark() << "update(ms): " << count << " " << update_time << std::endl;
        }
        if (count == 1048576) {
                    gettimeofday(&t2, NULL);
                    double update_time = ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0;
                    DistSSE::logger::log_benchmark() << "update(ms): " << count << " " << update_time << std::endl;
        }

        if(count>maxNum){
            // now tell server we have finished
            writer->WritesDone();
            Status status = writer->Finish();
            delete it;
            // end the process of evaluation
            break;
        }

        filename = it->key().ToString();
        value = it->value().ToString();



        std::vector <std::string> keywords;
        split(value, keywords, ',');
        for (const auto &keyword : keywords) {
//            std::cout << filename + " " + keyword << std::endl;
            writer->Write(client.gen_update_request("1", keyword, filename));
        }
        count++;
    }
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
    }
    return 0;
}

