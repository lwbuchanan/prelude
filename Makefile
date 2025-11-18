CXX := g++
CXXFLAGS := -Wall
CXXOBJFLAGS := $(CXXFLAGS) -c

BIN_PATH := bin
SRC_PATH := src
OBJ_PATH := $(BIN_PATH)/obj

TARGET_NAME := main
TARGET := $(BIN_PATH)/$(TARGET_NAME)

CXXSRC := $(foreach x, $(SRC_PATH), $(wildcard $(addprefix $(x)/*,.cpp)))
CXXOBJ := $(addprefix $(OBJ_PATH)/, $(addsuffix .o, $(notdir $(basename $(CXXSRC)))))

CLEAN_LIST := $(TARGET) $(CXXOBJ)

default: makedir all

$(TARGET): $(CXXOBJ)
	$(CXX) $(CXXFLAGS) -o $@ $(CXXOBJ)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c*
	$(CXX) $(CXXOBJFLAGS) -o $@ $<

# phony rules
.PHONY: run
run: all
	./$(TARGET)

.PHONY: makedir
makedir:
	@mkdir -p $(BIN_PATH) $(OBJ_PATH)

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	@echo CLEAN $(CLEAN_LIST)
	@rm -f $(CLEAN_LIST)
	@rm -r bin
