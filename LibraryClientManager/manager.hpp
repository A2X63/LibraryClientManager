#pragma once
#include <vector>
#include <string>
#include "member.hpp"

class MemberManager {
private:
    std::vector<Member> members;
    int nextId;

    Member* findById(int id);

public:
    MemberManager();

    // 기본 CRUD
    void addMember();
    void removeMember();
    void showAllMembers()       const;
    void showMemberDetail()     const;

    // 대출·반납
    void borrowBook();
    void returnBook();

    // 연체·등급
    void showOverdueMembers()   const;
    void collectFine();    // 연체 벌금 납부
    void showByGrade()          const;

    // 예약대기, 통계, 파일 I/O, 알림, 벌금납부 등은 다음 단계에…
};
