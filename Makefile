VPATH = $(shell find $(SRC_DIR) -type d)

RM := rm -rf

# Main directories
SRC_DIR = src
INC_DIR = inc
DEBUG_DIR = build/debug
RELEASE_DIR = build/release

# Sources and objects
CPP_SRCS = $(shell find $(SRC_DIR) -type f -iname *.cpp)	# Find all app cpp
CPP_DEBUG_OBJS = $(patsubst %.cpp,$(DEBUG_DIR)/%.o,$(notdir $(CPP_SRCS)))
CPP_RELEASE_OBJS = $(patsubst $(DEBUG_DIR)%, $(RELEASE_DIR)%, $(CPP_DEBUG_OBJS))

# Flags
COMMOMN_FLAGS = \
	-MD \
	-Wall \
	-pedantic \

CPP_FLAGS += \
	$(COMMOMN_FLAGS) \
	-std=c++17 \
	-I$(INC_DIR)

OPTIMIZATION    := -O0

BUILD_ARTIFACT_NAME = serializer
CXX = g++

###########################################################
# Phony targets
###########################################################
.PHONY: all dirs files clean

all: dirs main_build

main_build: $(DEBUG_DIR)/$(BUILD_ARTIFACT_NAME) $(RELEASE_DIR)/$(BUILD_ARTIFACT_NAME)

#######################################################################
# Debug target
#######################################################################
$(DEBUG_DIR)/$(BUILD_ARTIFACT_NAME): $(CPP_DEBUG_OBJS)
	$(CXX) -g $^ -o $@ $(CPP_FLAGS)

#############################################################################
# Release target
#############################################################################
$(RELEASE_DIR)/$(BUILD_ARTIFACT_NAME): $(CPP_RELEASE_OBJS)
	$(CXX) $^ -o $@ $(CPP_FLAGS) $(OPTIMIZATION)

#################################################
# CPP targets
#################################################
$(DEBUG_DIR)/%.o: %.cpp | $(DEBUG_DIR)
	$(CXX) -g $< -o $@ -c $(CPP_FLAGS)

$(RELEASE_DIR)/%.o: %.cpp | $(RELEASE_DIR)
	$(CXX) $< -o $@ -c $(CPP_FLAGS) $(OPTIMIZATION)

# Order-only prerequisites para crear directorios
$(DEBUG_DIR):
	@mkdir -p $(DEBUG_DIR)

$(RELEASE_DIR):
	@mkdir -p $(RELEASE_DIR)

#################################################
# Include dependencies
#################################################
-include $(DEBUG_DIR)/*.d
-include $(RELEASE_DIR)/*.d

dirs:
	@mkdir -p  $(SRC_DIR)
	@mkdir -p  $(DEBUG_DIR)
	@mkdir -p  $(RELEASE_DIR)

files:
	@echo "CPP"
	@echo $(CPP_SRCS)
	@echo $(CPP_DEBUG_OBJS)
	@echo $(CPP_RELEASE_OBJS)


clean:
	@$(RM) $(DEBUG_DIR)/* $(RELEASE_DIR)/*
	@echo "Clean!"
	@tree .