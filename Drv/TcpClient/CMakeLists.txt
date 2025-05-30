####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
####
restrict_platforms(Posix SOCKETS)

set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/TcpClient.fpp"
    "${CMAKE_CURRENT_LIST_DIR}/TcpClientComponentImpl.cpp"
)

# Necessary shared helpers
set(MOD_DEPS
    "Fw/Logger"
    "Drv/ByteStreamDriverModel"
    "Drv/Ip"
)

register_fprime_module()

### UTs ###
set(UT_SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/TcpClient.fpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/TcpClientTestMain.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/TcpClientTester.cpp"
)
set(UT_MOD_DEPS
    STest
    SocketTestHelper
)
set(UT_AUTO_HELPERS ON)
register_fprime_ut()
set (UT_TARGET_NAME "${FPRIME_CURRENT_MODULE}_ut_exe")
if (TARGET "${UT_TARGET_NAME}")
    target_compile_options("${UT_TARGET_NAME}" PRIVATE -Wno-conversion)
endif()
