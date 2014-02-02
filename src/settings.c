#include<pebble.h>
#include<main.h>
#include<settings.h>
#include<persist_const.h>

//Actual settings stored here
uint32_t boolean_flags = SETTINGS_BOOL_SHOW_CLOCK_HEADER;
uint32_t design_flags = 0;

void settings_persist() { //saves settings to persistent storage.
	persist_write_int(PERSIST_BOOL_FLAG_SETTINGS, boolean_flags);
	persist_write_int(PERSIST_DESIGN_SETTINGS, design_flags);
}

void settings_restore_persisted() { //restores settings from persistent storage if existing
	if (persist_exists(PERSIST_BOOL_FLAG_SETTINGS)) {
		boolean_flags = persist_read_int(PERSIST_BOOL_FLAG_SETTINGS);
		design_flags = persist_read_int(PERSIST_DESIGN_SETTINGS);
	}
}

uint32_t settings_get_bool_flags() { //getter for general settings (details in settings.h)
	return boolean_flags;
}

void settings_set(uint32_t flags, uint32_t design) { // Will callback to main.h and persist on changes
	bool changed = false;
	if (boolean_flags != flags) {
		boolean_flags = flags;
		changed = true;
	}
	
	if (design != design_flags) {
		design_flags = design;
		changed = true;
	}
	
	if (changed) {
		handle_new_settings();
		settings_persist();
	}
}

uint32_t settings_get_design() { //getter for design settings (details in settings.h)
	return design_flags;
}