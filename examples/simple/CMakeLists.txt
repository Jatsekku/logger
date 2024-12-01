project(loggerSimpleExample)

# Create executable target named "simpleExample" and provide list of sources
add_executable(simpleExample
    module1.c
    module2.c
    module3.c
    main.c)

# Link logger-static library to target
target_link_libraries(simpleExample
    PRIVATE
    logger-static)

# Install the example executable
install(TARGETS simpleExample DESTINATION ${EXAMPLES_INSTALL_PATH}/bin)
