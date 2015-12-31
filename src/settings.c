#include<pebble.h>
#include<main.h>
#include<settings.h>
#include<persist_const.h>

//Actual settings stored here
uint32_t boolean_flags = SETTINGS_BOOL_SHOW_CLOCK_HEADER;

void settings_persist() { //saves settings to persistent storage. 
	persist_write_int(PERSIST_BOOL_FLAG_SETTINGS, boolean_flags);
}

void settings_restore_persisted() { //restores settings from persistent storage if existing
	if (persist_exists(PERSIST_BOOL_FLAG_SETTINGS)) {
		boolean_flags = persist_read_int(PERSIST_BOOL_FLAG_SETTINGS);
	}
}

uint32_t settings_get_bool_flags() { //getter for general settings (details in settings.h)

  uint32_t ret = boolean_flags;
  //SETTINGS_BOOL_LIMIT_PERSIST
#if FORCE_SETTINGS
  ret = SETTINGS_BOOL_SHOW_CLOCK_HEADER | SETTINGS_BOOL_FONT_SIZE0 | SETTINGS_BOOL_HEADER_SIZE0 | SETTINGS_BOOL_COUNTDOWNS;
#endif
  //APP_LOG(APP_LOG_LEVEL_DEBUG, "%lx > %lx", boolean_flags, ret);
	return ret;
}

void settings_set(uint32_t flags) { // Will callback to main.h and persist on changes
	bool changed = false;
	if (boolean_flags != flags) {
		boolean_flags = flags;
		changed = true;
	}
	
	if (changed) {
		handle_new_settings();
		settings_persist();
	}
}
