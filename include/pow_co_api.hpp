#ifndef BOOSTMINER_POW_CO_API
#define BOOSTMINER_POW_CO_API

#include <data/networking/HTTP_client.hpp>
#include <gigamonkey/boost/boost.hpp>

using namespace Gigamonkey;

struct inpoint : Bitcoin::outpoint {
    using Bitcoin::outpoint::outpoint;
    bool valid() const {
        return this->Digest.valid();
    }
};

struct pow_co : networking::HTTP_client {
    
    pow_co(networking::HTTP &http) : 
        networking::HTTP_client{http, networking::REST{"https", "pow.co"}, tools::rate_limiter{3, 1}} {}
    
    list<Boost::prevout> jobs(uint32 limit = 10);
    
    Boost::prevout job(const Bitcoin::txid &);
    Boost::prevout job(const Bitcoin::outpoint &);
    
    inpoint spends(const Bitcoin::outpoint &);
    
    void submit_proof(const Bitcoin::txid &);
    void submit_proof(const inpoint &);
    
    bool broadcast(const bytes &);
    
    void submit_proof_GET(const Bitcoin::txid &);
    void submit_proof_POST(const Bitcoin::txid &);
    
};

void inline pow_co::submit_proof(const Bitcoin::txid &tx) {
    return submit_proof_GET(tx);
}

#endif
