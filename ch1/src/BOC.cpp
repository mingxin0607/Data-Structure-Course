#include "BOC.h"
#include "iostream"

int BOC::addUser(AccountInfo account_info){
    // allocate space for new node
    AccountListNode* new_node = new AccountListNode();
    new_node->account_info_ = account_info;
    AccountListNode* p = dummy_head;
    int new_id = 1; // attemp to assign this id to the new account
    while (p->next){
        if (p->next->account_id_ > new_id){ 
            // there is an unused id
            // take the free id and insert the new node
            new_node->account_id_ = new_id;
            new_node->next = p->next;
            p->next = new_node;
            return new_id;
        }
        new_id++;
        p = p->next;
    }
    // after iteraing the linked list, no spare id is found
    // so create a new id at the back
    new_node->account_id_ = new_id;
    new_node->next = nullptr;
    p->next = new_node;
    return new_id;
}

bool BOC::deleteUser(int user_id){
    AccountListNode* p = dummy_head;
    while(p->next){
        if (p->next->account_id_ == user_id){
            // found the target id
            AccountListNode* temp = p->next;
            p->next = p->next->next;
            delete temp;
            return true;
        }
        p = p->next;
    }
    // user id not found
    return false;
}

bool BOC::payUserToUser(int payer_id, int payee_id, double amount){
    AccountListNode* p = dummy_head;
    AccountListNode* p_payer = nullptr; // pointer of payer node
    AccountListNode* p_payee = nullptr; // pointer of payee node

    while(p->next){
        if (payer_id == p->next->account_id_){
            if (p->next->account_info_.deposit < amount){
                std::cerr << "not enough money" << std::endl;
                return false;
            }
            p_payer = p->next;
        }
        if (payee_id == p->next->account_id_){
            p_payee = p->next;
        }
        p = p->next;
    }
    if (p_payee == nullptr || p_payer == nullptr) {
        std::cerr << "payer or payee not found" << std::endl;
        return false; // payer_id or payee_id is not valid
    }

    p_payer->account_info_.deposit -= amount;
    p_payee->account_info_.deposit += amount;
    return true;
}

int BOC::getMedianID(){
    AccountListNode* p1 = dummy_head->next;
    AccountListNode* p2 = p1;
    while(p2){
        p2 = p2->next;
        if (!p2) {
            break;
        }
        p2 = p2->next;
        if (!p2) {
            break;
        }
        p1 = p1->next;
    }
    return p1->account_id_;
}

bool BOC::mergeAccounts(int id1, int id2){
    AccountListNode* p = dummy_head;
    AccountListNode* p1 = nullptr; // pointer of first account
    AccountListNode* p2 = nullptr; // pointer of second account

    while(p->next){
        if (id1 == p->next->account_id_){
            p1 = p->next;
        }
        if (id2 == p->next->account_id_){
            p2 = p->next;
        }
        p = p->next;
    }
    if (p1 == nullptr || p2 == nullptr) {
        std::cerr << "id1 or id2 not found" << std::endl;
        return false; // id1 or id2 is not valid
    }
    if (p1->account_info_.address != p2->account_info_.address || \
    p1->account_info_.name != p2->account_info_.name || \
    p1->account_info_.social_security != p2->account_info_.social_security){
        std::cerr << "account info not match" << std::endl;
        return false;
    }
    p1->account_info_.deposit += p2->account_info_.deposit;
    deleteUser(id2);
    return true;
}

void BOC::printInfo(){
    AccountListNode* p = dummy_head;
    while (p->next) {
        std::cout << "account id: " << p->next->account_id_ << std::endl;
        std::cout << "name: " << p->next->account_info_.name \
        << " address: " << p->next->account_info_.address \
        << "\nssn: " << p->next->account_info_.social_security \
        << " deposit: " << p->next->account_info_.deposit << std::endl;
        p = p->next;
    }
    std::cout << "--------------------------------" << std::endl;
}

void BOC::mergeBanks(BOC bola){
    AccountListNode* p1 = dummy_head;
    AccountListNode* p2 = bola.dummy_head;
    while(p1->next && p2->next){
        if (p1->next->account_id_ == p2->next->account_id_){
            AccountInfo new_account = p2->next->account_info_;
            this->addUser(new_account);
            p1 = p1->next;
            p2 = p2->next;
        }
        else if(p1->next->account_id_ < p2->next->account_id_){
            p1 = p1->next;
        }
        else{
            p2 = p2->next;
        }
        
    }
    if (p2->next){
        p1->next = p2->next;
    }
}