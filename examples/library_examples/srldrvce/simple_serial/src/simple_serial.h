/**
 * Initializes the serial connection.
 * If there are multiple serial devices connected, only a single serial device
 * will be used.
 * If no serial device is present, the next serial device to be connected will
 * automatically be initialized.
 * For more precise control over which device is used, consider using the
 * srldrvce library directly.
 *
 * @param baud_rate The baud rate to use for the serial connection.
 */
void serial_Begin(int baud_rate);

/**
 * Read data from serial.
 * This function is non-blocking. If there are fewer than size bytes that have
 * been received but not read, this function will read all currently available
 * bytes, rather than waiting for new data to be received.
 *
 * @param buffer The buffer to read data into.
 * @param size The number of bytes to read.
 * @returns The number of bytes actually read.
 */
int serial_Read(void *buffer, size_t size);

/**
 * Write data to serial.
 * This function is non-blocking.
 *
 * @param buffer The buffer containing the data to write.
 * @param size The number of bytes to write.
 * @returns The number of bytes actually written.
 */
int serial_Write(const void *buffer, size_t size);

/**
 * Writes data to serial based on a format specifier.
 * This function takes the same parameters as the printf function, but outputs
 * to the serial device rather than to the screen.
 *
 * @param format The format specifier.
 */
int serial_printf(const char *format, ...);

/**
 * De-initialize the serial connection.
 *
 * You must call this function before returning to the OS.
 */
void serial_End();
