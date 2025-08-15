#ifndef APP_H
#define APP_H
typedef void (*app_entry_t)(void);

typedef struct {
    const char* id;
    const char* name;
    app_entry_t entry;
    int builtin;
} BApp;

void app_register(const BApp* app);
int app_count(void);
const BApp* app_get(int idx);
int app_launch_by_id(const char* id);

void app_init_builtins(void);
void app_scan_bunapps(void);
#endif
