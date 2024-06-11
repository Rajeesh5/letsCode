#include <iostream>
#include <memory>
#include "TeamLeader.hpp"
#include "ProjectLeader.hpp"
#include "HR.hpp"
#include "Manager.hpp"

int main() {
    auto teamLeader = std::make_shared<TeamLeader>();
    auto projectLeader = std::make_shared<ProjectLeader>();
    auto hr = std::make_shared<HR>();
    auto manager = std::make_shared<Manager>();

    teamLeader->setSuperVisor(projectLeader);
    projectLeader->setSuperVisor(hr);
    hr->setSuperVisor(manager);

    Leave leave1(5, 4, ReasonType::REGULAR);
    std::cout << teamLeader->applyLeave(leave1) << std::endl;

    Leave leave2(5, 5, ReasonType::REGULAR);
    std::cout << teamLeader->applyLeave(leave2) << std::endl;

    Leave leave3(12, 3, ReasonType::REGULAR);
    std::cout << teamLeader->applyLeave(leave3) << std::endl;

    Leave leave4(18, 2, ReasonType::CRITICAL);
    std::cout << teamLeader->applyLeave(leave4) << std::endl;

    Leave leave5(18, 2, ReasonType::REGULAR);
    std::cout << teamLeader->applyLeave(leave5) << std::endl;

    Leave leave6(30, 2, ReasonType::SPECIAL);
    std::cout << teamLeader->applyLeave(leave6) << std::endl;

    return 0;
}
