####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
# Note: using PROJECT_NAME as EXECUTABLE_NAME
####
register_fprime_module(
    AUTOCODER_INPUTS
        "${CMAKE_CURRENT_LIST_DIR}/File.fpp"
        "${CMAKE_CURRENT_LIST_DIR}/Task.fpp"
        "${CMAKE_CURRENT_LIST_DIR}/Mutex.fpp"
        "${CMAKE_CURRENT_LIST_DIR}/Directory.fpp"
        "${CMAKE_CURRENT_LIST_DIR}/FileSystem.fpp"
        "${CMAKE_CURRENT_LIST_DIR}/Generic.fpp"
        "${CMAKE_CURRENT_LIST_DIR}/RawTime.fpp"
        "${CMAKE_CURRENT_LIST_DIR}/Queue.fpp"
    SOURCES
        "${CMAKE_CURRENT_LIST_DIR}/Models.cpp"
    DEPENDS
        Fw_Types
)
