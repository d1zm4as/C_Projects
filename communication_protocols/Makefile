CC ?= gcc
CFLAGS ?= -Wall -Wextra -O2 -std=c11

BUILD_DIR := build
COMMON_DIR := common
PROT_DIR := protocols

UART_SRC := $(PROT_DIR)/uart/src/uart_framing.c \
	$(PROT_DIR)/uart/src/uart_example.c \
	$(COMMON_DIR)/crc16.c $(COMMON_DIR)/hex_dump.c
UART_INC := -I$(PROT_DIR)/uart/include -I$(COMMON_DIR)

SPI_SRC := $(PROT_DIR)/spi/src/spi_protocol.c $(PROT_DIR)/spi/src/spi_example.c
SPI_INC := -I$(PROT_DIR)/spi/include

I2C_SRC := $(PROT_DIR)/i2c/src/i2c_device.c $(PROT_DIR)/i2c/src/i2c_example.c
I2C_INC := -I$(PROT_DIR)/i2c/include

UDP_SERVER_SRC := $(PROT_DIR)/udp/src/udp_echo_server.c
UDP_CLIENT_SRC := $(PROT_DIR)/udp/src/udp_echo_client.c

TCP_SERVER_SRC := $(PROT_DIR)/tcp/src/tcp_echo_server.c
TCP_CLIENT_SRC := $(PROT_DIR)/tcp/src/tcp_echo_client.c

CAN_SRC := $(PROT_DIR)/can/src/can_frame.c $(PROT_DIR)/can/src/can_example.c \
	$(COMMON_DIR)/hex_dump.c
CAN_INC := -I$(PROT_DIR)/can/include -I$(COMMON_DIR)

MODBUS_SRC := $(PROT_DIR)/modbus_rtu/src/modbus_rtu.c \
	$(PROT_DIR)/modbus_rtu/src/modbus_example.c \
	$(COMMON_DIR)/crc16.c $(COMMON_DIR)/hex_dump.c
MODBUS_INC := -I$(PROT_DIR)/modbus_rtu/include -I$(COMMON_DIR)

MQTT_SRC := $(PROT_DIR)/mqtt/src/mqtt_simple.c $(PROT_DIR)/mqtt/src/mqtt_example.c \
	$(COMMON_DIR)/hex_dump.c
MQTT_INC := -I$(PROT_DIR)/mqtt/include -I$(COMMON_DIR)

ZIGBEE_SRC := $(PROT_DIR)/zigbee/src/zigbee_aps.c $(PROT_DIR)/zigbee/src/zigbee_example.c \
	$(COMMON_DIR)/hex_dump.c
ZIGBEE_INC := -I$(PROT_DIR)/zigbee/include -I$(COMMON_DIR)

ALL_BINS := \
	$(BUILD_DIR)/uart_example \
	$(BUILD_DIR)/spi_example \
	$(BUILD_DIR)/i2c_example \
	$(BUILD_DIR)/udp_echo_server \
	$(BUILD_DIR)/udp_echo_client \
	$(BUILD_DIR)/tcp_echo_server \
	$(BUILD_DIR)/tcp_echo_client \
	$(BUILD_DIR)/can_example \
	$(BUILD_DIR)/modbus_example \
	$(BUILD_DIR)/mqtt_example \
	$(BUILD_DIR)/zigbee_example

.PHONY: all clean

all: $(ALL_BINS)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/uart_example: $(UART_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(UART_INC) $^ -o $@

$(BUILD_DIR)/spi_example: $(SPI_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(SPI_INC) $^ -o $@

$(BUILD_DIR)/i2c_example: $(I2C_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(I2C_INC) $^ -o $@

$(BUILD_DIR)/udp_echo_server: $(UDP_SERVER_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/udp_echo_client: $(UDP_CLIENT_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/tcp_echo_server: $(TCP_SERVER_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/tcp_echo_client: $(TCP_CLIENT_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $^ -o $@

$(BUILD_DIR)/can_example: $(CAN_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CAN_INC) $^ -o $@

$(BUILD_DIR)/modbus_example: $(MODBUS_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(MODBUS_INC) $^ -o $@

$(BUILD_DIR)/mqtt_example: $(MQTT_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(MQTT_INC) $^ -o $@

$(BUILD_DIR)/zigbee_example: $(ZIGBEE_SRC) | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(ZIGBEE_INC) $^ -o $@

clean:
	rm -rf $(BUILD_DIR)
