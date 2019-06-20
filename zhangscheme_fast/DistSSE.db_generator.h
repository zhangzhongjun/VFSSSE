#include "DistSSE.client.h"
#include "DistSSE.Util.h"
#include <cmath>
#include <chrono>

namespace DistSSE {

    static std::mutex print_mtx;


    /**
    * update the database
    *
    * @param client the client
    * @param thread_id 所在线程的id
    * @param N_entries 所在线程应该生成多少个entries
    */
    static void generation_job_2(Client *client, std::string keyword, unsigned int thread_id, size_t N_entries) {
        //std::string id_string = std::to_string(thread_id);
        CryptoPP::AutoSeededRandomPool prng;
        int ind_len = AES::BLOCKSIZE / 2; // AES::BLOCKSIZE = 16
        byte tmp[ind_len];
        // for gRPC
        UpdateRequestMessage request;
        ClientContext context;
        ExecuteStatus exec_status;
        std::unique_ptr <RPC::Stub> stub_(
                RPC::NewStub(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials())));
        std::unique_ptr <ClientWriterInterface<UpdateRequestMessage>> writer(
                stub_->batch_update(&context, &exec_status));
        for (size_t i = 0; i < N_entries; i++) {
            prng.GenerateBlock(tmp, sizeof(tmp));
            std::string ind = /*Util.str2hex*/(std::string((const char *) tmp, ind_len));
            writer->Write(client->gen_update_request("1", keyword, ind));
        }
        // now tell server we have finished
        writer->WritesDone();
        Status status = writer->Finish();

        std::string log = "Random DB generation: thread " + std::to_string(thread_id) + " completed: " +
                          std::to_string(N_entries) + " keyword-filename";
        logger::log(logger::INFO) << log << std::endl;
    }

    /**
      * update the database
      *
      * @param client 客户端对象
      * @param N_entries 全部的entries数目
      * @param keyword 关键词
      * @param n_threads 线程数
      */
    void gen_db_2(Client &client, size_t N_entries, std::string keyword, unsigned int n_threads) {
        logger::log(logger::INFO) << "in gen_db_2" << std::endl;
        std::vector <std::thread> threads;
        struct timeval t1, t2;
        gettimeofday(&t1, NULL);
        int numOfEntries1 = N_entries / n_threads;
        int numOfEntries2 = N_entries / n_threads + N_entries % n_threads;
        for (unsigned int i = 0; i < n_threads - 1; i++) {
            threads.push_back(std::thread(generation_job_2, &client, keyword, i, numOfEntries1));
        }
        threads.push_back(std::thread(generation_job_2, &client, keyword, n_threads - 1, numOfEntries2));
        for (unsigned int i = 0; i < n_threads; i++) {
            threads[i].join();
        }
        gettimeofday(&t2, NULL);
        logger::log_benchmark()
                << "keyword: " + keyword + " " + std::to_string(N_entries) + " entries " + "update time: "
                << ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0 << " ms"
                << std::endl;
        logger::log(logger::INFO)
                << "keyword: " + keyword + " " + std::to_string(N_entries) + " entries " + "update time: "
                << ((t2.tv_sec - t1.tv_sec) * 1000000.0 + t2.tv_usec - t1.tv_usec) / 1000.0 << " ms"
                << std::endl;
        // client->end_update_session();
    }

} //namespace DistSSE
