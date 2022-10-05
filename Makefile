TARGET_EXEC := BallInBox

BUILD_DIR := build
SRC_DIR := src
LIB_DIR := lib

SRCS := $(shell find $(SRC_DIR) -name '*.cpp')
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_DIR := include include/simplecpp
INC_FLAGS := $(addprefix -I,$(INC_DIR))

CXXFLAGS := $(INC_FLAGS) -MMD -MP
LDFLAGS := $(addprefix -L,$(LIB_DIR))
LIBFLAGS := -lsprite -lX11

.PHONY: all clean

all: $(TARGET_EXEC)

$(TARGET_EXEC): $(OBJS)
	g++ $(LDFLAGS) -o $@ $^ $(LIBFLAGS)	# loading libraries last to ensure all required functions are loaded (see man g++)

$(BUILD_DIR)/%.cpp.o: %.cpp
	@mkdir -p $(dir $@)
	g++ -c $(CXXFLAGS) -o $@ $<

clean:
	rm -rf $(BUILD_DIR)

-include $(DEPS)
