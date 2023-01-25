#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

enum {
    HOOK_TYPE_CURSOR = 0,
    HOOK_TYPE_LIBRARY,
    HOOK_TYPE_RAW_KEY,
    HOOK_TYPE_GET_CSC,
    HOOK_TYPE_HOMESCREEN,
    HOOK_TYPE_WINDOW,
    HOOK_TYPE_GRAPH,
    HOOK_TYPE_Y_EQUALS,
    HOOK_TYPE_FONT,
    HOOK_TYPE_REGRAPH,
    HOOK_TYPE_GRAPHICS,
    HOOK_TYPE_TRACE,
    HOOK_TYPE_PARSER,
    HOOK_TYPE_APP_CHANGE,
    HOOK_TYPE_CATALOG1,
    HOOK_TYPE_HELP,
    HOOK_TYPE_CX_REDISP,
    HOOK_TYPE_MENU,
    HOOK_TYPE_CATALOG2,
    HOOK_TYPE_TOKEN,
    HOOK_TYPE_LOCALIZE,
    HOOK_TYPE_SILENT_LINK,
    HOOK_TYPE_USB_ACTIVITY,
    HOOK_NUM_TYPES,
    HOOK_TYPE_UNKNOWN = 0xFF
};
typedef uint8_t hook_type_t;

enum {
    HOOK_SUCCESS = 0,
    HOOK_ERROR_NO_MATCHING_ID,
    HOOK_ERROR_INVALID_USER_HOOK,
    HOOK_ERROR_UNKNOWN_TYPE,
    HOOK_ERROR_DESCRIPTION_TOO_LONG,
    HOOK_ERROR_INTERNAL_DATABASE_IO,
    HOOK_ERROR_NEEDS_GC,
    HOOK_ERROR_DATABASE_CORRUPTED,
    HOOK_ERROR_UNKNOWN_DATABASE_VERSION
};
typedef uint8_t hook_error_t;

/**
 * A hook in memory, as described in
 * https://wikiti.brandonw.net/index.php?title=83Plus:OS:Hooks
 *
 * Installing and chaining is handled automatically by this library.
 *
 * Additionally, your hook should reset bit 0 of (flags-10) when returning a
 * value to the OS, or set the bit if other hooks of the same type should be
 * processed.
 */
typedef void hook_t;

/**
 * Apply changes made to the hook database
 * @return An error code or HOOK_SUCCESS
 */
hook_error_t hook_Sync(void);

/**
 * Discard all changes to the hook database since the last hook_Sync()
 * @return An error code or HOOK_SUCCESS
 */
hook_error_t hook_Discard(void);

/**
 * Installs a hook.
 *
 * If @param size is nonzero, a copy of @param hook will be created.
 * As a result, @param hook must be position-independent.
 *
 * If @param size is zero, @param hook will not be copied but used in-place.
 * This is not recommended except for apps, as hooks stored in RAM will
 * become invalid after the program exits.
 *
 * If another hook with the same ID is already installed, the old hook will be
 * replaced with the new one. The old hook's priority will be preserved.
 *
 * @param id A unique id for the hook. This must be unique among all programs
 * that use this library. You should register your ID on this page:
 * https://github.com/commandblockguy/capnhook/wiki/Hook-ID-Registry
 * @param hook A pointer to the hook to install. If @param size is nonzero,
 * must be position-independent.
 * @param size The size of the hook. If zero, the hook will be used in-place
 * rather than being copied.
 * @param type The hook type determines what type of OS event the hook will
 * trigger on.
 * @param priority Hooks with lower priority values are called prior to hooks
 * with higher priority values.
 * @param description A human-readable description of the hook, up to 255
 * chars in length.
 * @return An error code or HOOK_SUCCESS
 */
hook_error_t hook_Install(uint24_t id, hook_t *hook, size_t size, hook_type_t type, uint8_t priority, const char *description);

/**
 * Uninstall a hook
 * @param id The hook ID
 * @return An error code or HOOK_SUCCESS
 */
hook_error_t hook_Uninstall(uint24_t id);

/**
 * Sets the priority of a hook
 * @param id The hook ID
 * @param priority Hooks with lower priority values are called prior to hooks
 * with higher priority values.
 * @return An error code or HOOK_SUCCESS
 */
hook_error_t hook_SetPriority(uint24_t id, uint8_t priority);

/**
 * Enable a hook
 * @param id The hook ID
 * @return An error code or HOOK_SUCCESS
 */
hook_error_t hook_Enable(uint24_t id);

/**
 * Disable a hook
 * @param id The hook ID
 * @return An error code or HOOK_SUCCESS
 */
hook_error_t hook_Disable(uint24_t id);

/**
 * Check if a hook is installed
 * @param id The hook ID
 * @param result Set to 1 if the hook is installed, or 0 if it is not
 * @return An error code or HOOK_SUCCESS
 */
hook_error_t hook_IsInstalled(uint24_t id, bool *result);

/**
 * Get a pointer to a hook
 * @param id The hook ID
 * @param result Set to a pointer to the hook
 * @return An error code or HOOK_SUCCESS
 */
hook_error_t hook_GetHook(uint24_t id, hook_t **result);

/**
 * Get a hook's type
 * @param id The hook ID
 * @param result Set to the hook's type
 * @return An error code or HOOK_SUCCESS
 */
hook_error_t hook_GetType(uint24_t id, hook_type_t *result);

/**
 * Get the priority of a hook
 * @param id The hook ID
 * @param result Set to the hook's priority
 * @return An error code or HOOK_SUCCESS
 */
hook_error_t hook_GetPriority(uint24_t id, uint8_t *result);

/**
 * Check if a hook is enabled
 * @param id The hook ID
 * @param result Set to 1 if the hook is enabled or 0 otherwise
 * @return An error code or HOOK_SUCCESS
 */
hook_error_t hook_IsEnabled(uint24_t id, bool *result);

/**
 * Get the description of a hook
 * @param id The hook ID
 * @param result Set to a pointer to the hook description
 * @return An error code or HOOK_SUCCESS
 */
hook_error_t hook_GetDescription(uint24_t id, char **result);

/**
 * Check if a hook is valid.
 * A hook is valid if the first byte is 0x83
 * @param id The hook ID
 * @return HOOK_SUCCESS if hook is valid, HOOK_ERROR_INVALID_USER_HOOK if
 * invalid, or another error
 */
hook_error_t hook_CheckValidity(uint24_t id);

/**
 * Iterate through all hook IDs one at a time.
 *
 * @param id Set to the current hook ID. Set this to -1 to start searching.
 * @return HOOK_SUCCESS if @param id was set to the next hook ID,
 * HOOK_ERROR_NO_MATCHING_HOOK once all IDs have already been seen, or another
 * error
 */
hook_error_t hook_Next(uint24_t *id);
