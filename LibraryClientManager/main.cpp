// main.cpp
#include <iostream>
#include "manager.hpp"

void showMenu() {
    std::cout
        << "\n===== 도서관 회원관리 =====\n"
        << "1. 회원등록\n"
        << "2. 회원삭제\n"
        << "3. 전체회원조회\n"
        << "4. 회원상세조회\n"
        << "5. 대출 신청\n"
        << "6. 반납 처리\n"
        << "7. 연체회원목록\n"
        << "8. 등급별조회\n"
        << "9. 벌금 납부\n"
        << "0. 종료\n"
        << "선택> ";
}

int main() {
    MemberManager mgr;
    int choice;
    do {
        showMenu();
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
        case 1: mgr.addMember();        break;
        case 2: mgr.removeMember();     break;
        case 3: mgr.showAllMembers();   break;
        case 4: mgr.showMemberDetail(); break;
        case 5: mgr.borrowBook();       break;
        case 6: mgr.returnBook();       break;
        case 7: mgr.showOverdueMembers(); break;
        case 8: mgr.showByGrade();      break;
        case 9: mgr.collectFine();        break;
        case 0: std::cout << "종료합니다.\n"; break;
        default: std::cout << "잘못된 선택\n";
        }
    } while (choice != 0);

    return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
