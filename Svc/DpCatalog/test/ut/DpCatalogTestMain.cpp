// ======================================================================
// \title  DpCatalogTestMain.cpp
// \author tcanham
// \brief  cpp file for DpCatalog component test main function
// ======================================================================

#include "DpCatalogTester.hpp"
#include <Svc/DpCatalog/DpCatalog.hpp>
#include <list>

TEST(NominalManual, initTest) {
    Svc::DpCatalogTester tester;
    tester.doInit();
}

TEST(NominalManual, TreeTestManual1) {

    Svc::DpCatalogTester tester;
    Fw::FileNameString dir;

    Svc::DpCatalog::DpStateEntry inputs[1];
    Svc::DpCatalog::DpStateEntry outputs[1];

    inputs[0].record.setid(1);
    inputs[0].record.setpriority(2);
    inputs[0].record.setstate(Fw::DpState::UNTRANSMITTED);
    inputs[0].record.settSec(1000);
    inputs[0].record.settSub(1500);
    inputs[0].record.setsize(100);

    outputs[0].record.setid(1);
    outputs[0].record.setpriority(2);
    outputs[0].record.setstate(Fw::DpState::UNTRANSMITTED);
    outputs[0].record.settSec(1000);
    outputs[0].record.settSub(1500);
    outputs[0].record.setsize(100);

    tester.testTree(
        inputs,
        outputs,
        1
    );

}

TEST(NominalManual, TreeTestManual2) {

    Svc::DpCatalogTester tester;
    Fw::FileNameString dir;

    Svc::DpCatalog::DpStateEntry inputs[2];
    Svc::DpCatalog::DpStateEntry outputs[2];

    inputs[0].record.setid(1);
    inputs[0].record.setpriority(2);
    inputs[0].record.setstate(Fw::DpState::UNTRANSMITTED);
    inputs[0].record.settSec(1000);
    inputs[0].record.settSub(1500);
    inputs[0].record.setsize(100);

    inputs[1].record.setid(2);
    inputs[1].record.setpriority(1);
    inputs[1].record.setstate(Fw::DpState::UNTRANSMITTED);
    inputs[1].record.settSec(1000);
    inputs[1].record.settSub(1500);
    inputs[1].record.setsize(100);


    outputs[0].record = inputs[1].record;
    outputs[1].record = inputs[0].record;

    tester.testTree(
        inputs,
        outputs,
        FW_NUM_ARRAY_ELEMENTS(inputs)
    );

}

TEST(NominalManual, TreeTestManual3) {

    Svc::DpCatalogTester tester;
    Fw::FileNameString dir;

    Svc::DpCatalog::DpStateEntry inputs[3];
    Svc::DpCatalog::DpStateEntry outputs[3];

    inputs[0].record.setid(1);
    inputs[0].record.setpriority(2);
    inputs[0].record.setstate(Fw::DpState::UNTRANSMITTED);
    inputs[0].record.settSec(1000);
    inputs[0].record.settSub(1500);
    inputs[0].record.setsize(100);

    inputs[1].record.setid(2);
    inputs[1].record.setpriority(1);
    inputs[1].record.setstate(Fw::DpState::UNTRANSMITTED);
    inputs[1].record.settSec(1000);
    inputs[1].record.settSub(1500);
    inputs[1].record.setsize(100);

    inputs[2].record.setid(3);
    inputs[2].record.setpriority(3);
    inputs[2].record.setstate(Fw::DpState::UNTRANSMITTED);
    inputs[2].record.settSec(1000);
    inputs[2].record.settSub(1500);
    inputs[2].record.setsize(100);

    outputs[0].record = inputs[1].record;
    outputs[1].record = inputs[0].record;
    outputs[2].record = inputs[2].record;

    tester.testTree(
        inputs,
        outputs,
        FW_NUM_ARRAY_ELEMENTS(inputs)
    );

}

TEST(NominalManual, TreeTestManual5) {

    Svc::DpCatalogTester tester;
    Fw::FileNameString dir;

    Svc::DpCatalog::DpStateEntry inputs[5];
    Svc::DpCatalog::DpStateEntry outputs[5];

    inputs[0].record.setid(1);
    inputs[0].record.setpriority(2);
    inputs[0].record.setstate(Fw::DpState::UNTRANSMITTED);
    inputs[0].record.settSec(1000);
    inputs[0].record.settSub(1500);
    inputs[0].record.setsize(100);

    inputs[1].record.setid(2);
    inputs[1].record.setpriority(1);
    inputs[1].record.setstate(Fw::DpState::UNTRANSMITTED);
    inputs[1].record.settSec(1000);
    inputs[1].record.settSub(1500);
    inputs[1].record.setsize(100);

    inputs[2].record.setid(3);
    inputs[2].record.setpriority(3);
    inputs[2].record.setstate(Fw::DpState::UNTRANSMITTED);
    inputs[2].record.settSec(1000);
    inputs[2].record.settSub(1500);
    inputs[2].record.setsize(100);

    inputs[3].record.setid(4);
    inputs[3].record.setpriority(5);
    inputs[3].record.setstate(Fw::DpState::UNTRANSMITTED);
    inputs[3].record.settSec(1000);
    inputs[3].record.settSub(1500);
    inputs[3].record.setsize(100);

    inputs[4].record.setid(5);
    inputs[4].record.setpriority(4);
    inputs[4].record.setstate(Fw::DpState::UNTRANSMITTED);
    inputs[4].record.settSec(1000);
    inputs[4].record.settSub(1500);
    inputs[4].record.setsize(100);

    outputs[0].record = inputs[1].record;
    outputs[1].record = inputs[0].record;
    outputs[2].record = inputs[2].record;
    outputs[3].record = inputs[4].record;
    outputs[4].record = inputs[3].record;

    tester.testTree(
        inputs,
        outputs,
        FW_NUM_ARRAY_ELEMENTS(inputs)
    );

}

TEST(NominalManual, TreeTestManual1_Transmitted) {

    Svc::DpCatalogTester tester;
    Fw::FileNameString dir;

    Svc::DpCatalog::DpStateEntry inputs[1];
    Svc::DpCatalog::DpStateEntry outputs[1];

    inputs[0].record.setid(1);
    inputs[0].record.setpriority(2);
    inputs[0].record.setstate(Fw::DpState::TRANSMITTED);
    inputs[0].record.settSec(1000);
    inputs[0].record.settSub(1500);
    inputs[0].record.setsize(100);

    outputs[0].record.setstate(Fw::DpState::TRANSMITTED);

    tester.testTree(
        inputs,
        outputs,
        1
    );

}


TEST(NominalManual, TreeTestManual_All_Transmitted) {

    Svc::DpCatalogTester tester;
    Fw::FileNameString dir;

    Svc::DpCatalog::DpStateEntry inputs[5];
    Svc::DpCatalog::DpStateEntry outputs[5];

    inputs[0].record.setid(1);
    inputs[0].record.setpriority(2);
    inputs[0].record.setstate(Fw::DpState::TRANSMITTED);
    inputs[0].record.settSec(1000);
    inputs[0].record.settSub(1500);
    inputs[0].record.setsize(100);

    inputs[1].record.setid(2);
    inputs[1].record.setpriority(1);
    inputs[1].record.setstate(Fw::DpState::TRANSMITTED);
    inputs[1].record.settSec(1000);
    inputs[1].record.settSub(1500);
    inputs[1].record.setsize(100);

    inputs[2].record.setid(3);
    inputs[2].record.setpriority(3);
    inputs[2].record.setstate(Fw::DpState::TRANSMITTED);
    inputs[2].record.settSec(1000);
    inputs[2].record.settSub(1500);
    inputs[2].record.setsize(100);

    inputs[3].record.setid(4);
    inputs[3].record.setpriority(5);
    inputs[3].record.setstate(Fw::DpState::TRANSMITTED);
    inputs[3].record.settSec(1000);
    inputs[3].record.settSub(1500);
    inputs[3].record.setsize(100);

    inputs[4].record.setid(5);
    inputs[4].record.setpriority(4);
    inputs[4].record.setstate(Fw::DpState::TRANSMITTED);
    inputs[4].record.settSec(1000);
    inputs[4].record.settSub(1500);
    inputs[4].record.setsize(100);

    outputs[0].record.setstate(Fw::DpState::TRANSMITTED);
    outputs[1].record.setstate(Fw::DpState::TRANSMITTED);
    outputs[2].record.setstate(Fw::DpState::TRANSMITTED);
    outputs[3].record.setstate(Fw::DpState::TRANSMITTED);
    outputs[4].record.setstate(Fw::DpState::TRANSMITTED);


    tester.testTree(
        inputs,
        outputs,
        FW_NUM_ARRAY_ELEMENTS(inputs)
    );

}

bool EntryCompare(const Svc::DpCatalog::DpStateEntry& a, const Svc::DpCatalog::DpStateEntry& b) {

    if (a.record.getpriority() == b.record.getpriority()) { // check priority first - lower value = higher priority
        if (a.record.gettSec() == b.record.gettSec()) { // check time next - older = higher priority
            return a.record.getid() < b.record.getid(); // finally check ID - lower = higher priority
        } else {
            return a.record.gettSec() < b.record.gettSec();
        }
    } else {
        return a.record.getpriority() < b.record.getpriority();
    }

}

TEST(NominalManual, TreeTestRandomPriority) {

    static const FwIndexType NUM_ENTRIES = Svc::DP_MAX_FILES;
    static const FwIndexType NUM_ITERS = 100;

    for (FwIndexType iter = 0; iter < NUM_ITERS; iter++) {

        Svc::DpCatalog::DpStateEntry inputs[NUM_ENTRIES];
        Svc::DpCatalog::DpStateEntry outputs[NUM_ENTRIES];

        Svc::DpCatalogTester tester;
        Fw::FileNameString dir;

        std::list<Svc::DpCatalog::DpStateEntry> entryList;

        srand(time(nullptr));

        // fill the input entries with random priorities
        for (FwIndexType entry = 0; entry < static_cast<FwIndexType>(FW_NUM_ARRAY_ELEMENTS(inputs)); entry++) {
            U32 randVal = rand()%NUM_ENTRIES;
            inputs[entry].record.setpriority(randVal);
            inputs[entry].record.setid(entry);
            inputs[entry].record.setstate(Fw::DpState::UNTRANSMITTED);
            inputs[entry].record.settSec(1000);
            inputs[entry].record.settSub(1500);
            inputs[entry].record.setsize(100);
            entryList.push_back(inputs[entry]);

        }

        entryList.sort(EntryCompare);

        FwIndexType entryIndex = 0;

        for (const auto& entry: entryList) {
            outputs[entryIndex].record.setpriority(entry.record.getpriority());
            outputs[entryIndex].record.setid(entry.record.getid());
            outputs[entryIndex].record.setstate(entry.record.getstate());
            outputs[entryIndex].record.settSec(1000);
            outputs[entryIndex].record.settSub(1500);
            outputs[entryIndex].record.setsize(100);
            entryIndex++;
        }

        tester.testTree(
            inputs,
            outputs,
            FW_NUM_ARRAY_ELEMENTS(inputs)
        );
    }
}

TEST(NominalManual, TreeTestRandomTime) {

    static const FwIndexType NUM_ENTRIES = Svc::DP_MAX_FILES;
    static const FwIndexType NUM_ITERS = 100;

    for (FwIndexType iter = 0; iter < NUM_ITERS; iter++) {

        Svc::DpCatalog::DpStateEntry inputs[NUM_ENTRIES];
        Svc::DpCatalog::DpStateEntry outputs[NUM_ENTRIES];

        Svc::DpCatalogTester tester;
        Fw::FileNameString dir;

        std::list<Svc::DpCatalog::DpStateEntry> entryList;

        srand(time(nullptr));

        // fill the input entries with random priorities
        for (FwIndexType entry = 0; entry < static_cast<FwIndexType>(FW_NUM_ARRAY_ELEMENTS(inputs)); entry++) {
            U32 randVal = rand()%NUM_ENTRIES;
            inputs[entry].record.setpriority(100);
            inputs[entry].record.setid(entry);
            inputs[entry].record.setstate(Fw::DpState::UNTRANSMITTED);
            inputs[entry].record.settSec(randVal);
            inputs[entry].record.settSub(1500);
            inputs[entry].record.setsize(100);
            entryList.push_back(inputs[entry]);

        }

        entryList.sort(EntryCompare);

        FwIndexType entryIndex = 0;

        for (const auto& entry: entryList) {
            outputs[entryIndex].record.setpriority(entry.record.getpriority());
            outputs[entryIndex].record.setid(entry.record.getid());
            outputs[entryIndex].record.setstate(entry.record.getstate());
            outputs[entryIndex].record.settSec(entry.record.gettSec());
            outputs[entryIndex].record.settSub(1500);
            outputs[entryIndex].record.setsize(100);
            entryIndex++;
        }

        tester.testTree(
            inputs,
            outputs,
            FW_NUM_ARRAY_ELEMENTS(inputs)
        );
    }
}

TEST(NominalManual, TreeTestRandomId) {

    static const FwIndexType NUM_ENTRIES = Svc::DP_MAX_FILES;
    static const FwIndexType NUM_ITERS = 100;

    for (FwIndexType iter = 0; iter < NUM_ITERS; iter++) {

        Svc::DpCatalog::DpStateEntry inputs[NUM_ENTRIES];
        Svc::DpCatalog::DpStateEntry outputs[NUM_ENTRIES];

        Svc::DpCatalogTester tester;
        Fw::FileNameString dir;

        std::list<Svc::DpCatalog::DpStateEntry> entryList;

        srand(time(nullptr));

        // fill the input entries with random priorities
        for (FwIndexType entry = 0; entry < static_cast<FwIndexType>(FW_NUM_ARRAY_ELEMENTS(inputs)); entry++) {
            U32 randVal = rand()%NUM_ENTRIES;
            inputs[entry].record.setpriority(100);
            inputs[entry].record.setid(randVal);
            inputs[entry].record.setstate(Fw::DpState::UNTRANSMITTED);
            inputs[entry].record.settSec(1000);
            inputs[entry].record.settSub(1500);
            inputs[entry].record.setsize(100);
            entryList.push_back(inputs[entry]);

        }

        entryList.sort(EntryCompare);

        FwIndexType entryIndex = 0;

        for (const auto& entry: entryList) {
            outputs[entryIndex].record.setpriority(entry.record.getpriority());
            outputs[entryIndex].record.setid(entry.record.getid());
            outputs[entryIndex].record.setstate(entry.record.getstate());
            outputs[entryIndex].record.settSec(entry.record.gettSec());
            outputs[entryIndex].record.settSub(1500);
            outputs[entryIndex].record.setsize(100);
            entryIndex++;
        }

        tester.testTree(
            inputs,
            outputs,
            FW_NUM_ARRAY_ELEMENTS(inputs)
        );
    }
}

TEST(NominalManual, TreeTestRandomPrioIdTime) {

    static const FwIndexType NUM_ENTRIES = Svc::DP_MAX_FILES;
    static const FwIndexType NUM_ITERS = 100;

    for (FwIndexType iter = 0; iter < NUM_ITERS; iter++) {

        Svc::DpCatalog::DpStateEntry inputs[NUM_ENTRIES];
        Svc::DpCatalog::DpStateEntry outputs[NUM_ENTRIES];

        Svc::DpCatalogTester tester;
        Fw::FileNameString dir;

        std::list<Svc::DpCatalog::DpStateEntry> entryList;

        srand(time(nullptr));

        // fill the input entries with random priorities
        for (FwIndexType entry = 0; entry < static_cast<FwIndexType>(FW_NUM_ARRAY_ELEMENTS(inputs)); entry++) {
            U32 randVal = rand()%NUM_ENTRIES;
            inputs[entry].record.setpriority(randVal);
            randVal = rand()%NUM_ENTRIES;
            inputs[entry].record.setid(randVal);
            inputs[entry].record.setstate(Fw::DpState::UNTRANSMITTED);
            randVal = rand()%NUM_ENTRIES;
            inputs[entry].record.settSec(randVal);
            inputs[entry].record.settSub(1500);
            inputs[entry].record.setsize(100);
            entryList.push_back(inputs[entry]);

        }

        entryList.sort(EntryCompare);

        FwIndexType entryIndex = 0;

        for (const auto& entry: entryList) {
            outputs[entryIndex].record.setpriority(entry.record.getpriority());
            outputs[entryIndex].record.setid(entry.record.getid());
            outputs[entryIndex].record.setstate(entry.record.getstate());
            outputs[entryIndex].record.settSec(entry.record.gettSec());
            outputs[entryIndex].record.settSub(1500);
            outputs[entryIndex].record.setsize(100);
            entryIndex++;
        }

        tester.testTree(
            inputs,
            outputs,
            FW_NUM_ARRAY_ELEMENTS(inputs)
        );
    }
}

TEST(NominalManual, DISABLED_TreeTestRandomTransmitted) {

    static const FwIndexType NUM_ENTRIES = 10;
    static const FwIndexType NUM_ITERS = 1;

    for (FwIndexType iter = 0; iter < NUM_ITERS; iter++) {

        Svc::DpCatalog::DpStateEntry inputs[NUM_ENTRIES];
        Svc::DpCatalog::DpStateEntry outputs[NUM_ENTRIES];

        Svc::DpCatalogTester tester;
        Fw::FileNameString dir;

        std::list<Svc::DpCatalog::DpStateEntry> entryList;

        srand(time(nullptr));

        // fill the input entries with random priorities
        for (FwIndexType entry = 0; entry < static_cast<FwIndexType>(FW_NUM_ARRAY_ELEMENTS(inputs)); entry++) {
            U32 randVal = rand()%NUM_ENTRIES;
            inputs[entry].record.setpriority(randVal);
            randVal = rand()%NUM_ENTRIES;
            inputs[entry].record.setid(randVal);
            randVal = rand()%NUM_ENTRIES;
            inputs[entry].record.settSec(randVal);
            inputs[entry].record.settSub(1500);
            inputs[entry].record.setsize(100);
            // randomly set if it is transmitted or not
            randVal = rand()%2;
            if (randVal == 0) {
                inputs[entry].record.setstate(Fw::DpState::UNTRANSMITTED);   
                // only put untransmitted products in list, since the catalog algorithm only returns untransmitted product IDs            
                entryList.push_back(inputs[entry]);
            } else {
                inputs[entry].record.setstate(Fw::DpState::TRANSMITTED);                
            }

        }

        entryList.sort(EntryCompare);

        FwIndexType entryIndex = 0;

        for (const auto& entry: entryList) {
            outputs[entryIndex].record.setpriority(entry.record.getpriority());
            outputs[entryIndex].record.setid(entry.record.getid());
            outputs[entryIndex].record.setstate(entry.record.getstate());
            outputs[entryIndex].record.settSec(entry.record.gettSec());
            outputs[entryIndex].record.settSub(1500);
            outputs[entryIndex].record.setsize(100);
            entryIndex++;
        }

        tester.testTree(
            inputs,
            outputs,
            FW_NUM_ARRAY_ELEMENTS(inputs)
        );
    }
}


TEST(NominalManual, DISABLED_OneDp) {

    Svc::DpCatalogTester tester;
    Fw::FileNameString dir;
    dir = "./DpTest";
    Fw::FileNameString stateFile("./DpState");

    Svc::DpCatalogTester::DpSet dpSet;
    dpSet.id = 0x123;
    dpSet.prio = 10;
    dpSet.state = Fw::DpState::UNTRANSMITTED;
    dpSet.time.set(1000,100);
    dpSet.dataSize = 100;
    dpSet.dir = dir.toChar();

    tester.readDps(
        &dir,
        1,
        stateFile,
        &dpSet,
        1
    );
}

TEST(NominalManual, DISABLED_FiveDp) {

    Svc::DpCatalogTester tester;
    Fw::FileNameString dirs[2];
    dirs[0] = "./DpTest1";
    dirs[1] = "./DpTest2";
    Fw::FileNameString stateFile("./DpState");

    Svc::DpCatalogTester::DpSet dpSet[5];
    
    dpSet[0].id = 123;
    dpSet[0].prio = 10;
    dpSet[0].state = Fw::DpState::UNTRANSMITTED;
    dpSet[0].time.set(1000,100);
    dpSet[0].dataSize = 100;
    dpSet[0].dir = dirs[0].toChar();

    dpSet[1].id = 234;
    dpSet[1].prio = 12;
    dpSet[1].state = Fw::DpState::UNTRANSMITTED;
    dpSet[1].time.set(2000,200);
    dpSet[1].dataSize = 50;
    dpSet[1].dir = dirs[1].toChar();

    dpSet[2].id = 1000000;
    dpSet[2].prio = 3;
    dpSet[2].state = Fw::DpState::UNTRANSMITTED;
    dpSet[2].time.set(3000,300);
    dpSet[2].dataSize = 200;
    dpSet[2].dir = dirs[0].toChar();

    dpSet[3].id = 2;
    dpSet[3].prio = 255;
    dpSet[3].state = Fw::DpState::UNTRANSMITTED;
    dpSet[3].time.set(1,500);
    dpSet[3].dataSize = 300;
    dpSet[3].dir = dirs[1].toChar();

    dpSet[4].id = 0x98765432;
    dpSet[4].prio = 17;
    dpSet[4].state = Fw::DpState::UNTRANSMITTED;
    dpSet[4].time.set(1000,100);
    dpSet[4].dataSize = 2;
    dpSet[4].dir = dirs[0].toChar();

    tester.readDps(
        dirs,
        2,
        stateFile,
        dpSet,
        5
    );
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
