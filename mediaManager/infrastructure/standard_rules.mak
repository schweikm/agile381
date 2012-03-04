############################
#### C LANGUAGE TARGETS ####
############################


$(OBJ_DIR)/%.o: %.c ../include/%.h
	@$(ECHO)
	@$(ECHO) "================================================================================"
	@$(MKDIR) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_DIRS) -o $@ $<
	@$(ECHO)
	@$(ECHO) "Will store \"$(abspath $@)\""
	@$(ECHO) "================================================================================"
	@$(ECHO)

$(OBJ_DIR)/%.o: %.c
	@$(ECHO)
	@$(ECHO) "================================================================================"
	@$(MKDIR) $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC_DIRS) -o $@ $<
	@$(ECHO)
	@$(ECHO) "Will store \"$(abspath $@)\""
	@$(ECHO) "================================================================================"
	@$(ECHO)


##############################
#### C++ LANGUAGE TARGETS ####
##############################


$(OBJ_DIR)/%.o: %.cpp ../include/%.h
	@$(ECHO)
	@$(ECHO) "================================================================================"
	@$(MKDIR) $(OBJ_DIR)
	$(CXX) $(C++FLAGS) $(INC_DIRS) -o $@ $<
	@$(ECHO)
	@$(ECHO) "Will store \"$(abspath $@)\""
	@$(ECHO) "================================================================================"
	@$(ECHO)
	
$(OBJ_DIR)/%.o: %.cpp
	@$(ECHO)
	@$(ECHO) "================================================================================"
	@$(MKDIR) $(OBJ_DIR)
	$(CXX) $(C++FLAGS) $(INC_DIRS) -o $@ $<
	@$(ECHO)
	@$(ECHO) "Will store \"$(abspath $@)\""
	@$(ECHO) "================================================================================"
	@$(ECHO)

$(UT_OBJ_DIR)/%.o: %.cpp
	@$(ECHO)
	@$(ECHO) "================================================================================"
	@$(MKDIR) $(UT_OBJ_DIR)
	$(CXX) $(GTEST_C_FLAGS) $(INC_DIRS) $(GTEST_INC_DIRS) -o $@ $<
	@$(ECHO)
	@$(ECHO) "Will store \"$(abspath $@)\""
	@$(ECHO) "================================================================================"
	@$(ECHO)



#########################
#### GENERIC TARGETS ####
#########################


clean:
	@$(RMDIR) $(OBJ_DIR)
	@$(RMDIR) $(UT_OBJ_DIR)
	@$(RMDIR) $(UT_DIR)
	@$(RM) $(LIB)
	@$(RM) $(EXE)
	@$(RM) $(TEST_DIR)/*

