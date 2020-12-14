include Makefile.include

.PHONY: all
all:
	@make sim_library;

CAPP_LIBS = lib$(MODULE).so
sim_library: gen_objects gen_shared_lib

gen_objects:
	@echo making simulator ...
	@if [ ! -d $(BUILD_DIR) ]; then echo mkdir -p $(BUILD_DIR); mkdir -p $(BUILD_DIR); fi
	@make -C $(INFRA_DIR)

gen_shared_lib:
	$(CC) $(OPTIONS) $(CFLAGS) -shared $(wildcard $(INFRA_DIR)/$(OBJDIR)/*$(OBJ_TYPE).o) -o $(BUILD_DIR)/$(CAPP_LIBS) $(LDFLAGS)

#############################################################################
.PHONY: clean
clean:
	@make -C $(INFRA_DIR) clean
	@rm -rf $(BUILD_DIR)
