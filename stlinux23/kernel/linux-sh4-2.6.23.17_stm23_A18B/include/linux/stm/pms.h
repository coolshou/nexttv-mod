/*
 * -------------------------------------------------------------------------
 * pms.h
 * -------------------------------------------------------------------------
 * (C) STMicroelectronics 2009
 * Author: Francesco M. Virlinzi <francesco.virlinzi@st.com>
 * -------------------------------------------------------------------------
 * May be copied or modified under the terms of the GNU General Public
 * License v.2 ONLY.  See linux/COPYING for more information.
 *
 * -------------------------------------------------------------------------
 */

#ifndef __pms_h__
#define __pms_h__

struct pms_state;
struct pms_object;
struct clk;
struct device;

struct pms_state *pms_create_state(char *name);
struct pms_state *pms_state_get(const char *name);
int pms_destry_state(struct pms_state *state);
int pms_set_current_states(char *buf);

static inline int pms_set_current_state(char *name){
	return pms_set_current_states(name);
}

char *pms_get_current_state(void);

struct pms_object *pms_register_cpu(int cpu_id);
struct pms_object *pms_register_clock(struct clk *clk);
struct pms_object *pms_register_device(struct device *device);

struct pms_object *pms_register_clock_by_name(char *clk_name);
struct pms_object *pms_register_device_by_path(char *dev_path);

int pms_unregister_cpu(int cpu_id);
int pms_unregister_clock(struct clk *clk);
int pms_unregister_device(struct device *dev);

int pms_set_constraint(struct pms_state *state, struct pms_object *obj,
		unsigned long value);

int pms_check_valid(struct pms_state *a, struct pms_state *b);

int pms_set_wakeup(struct pms_object *obj, int enable);
int pms_get_wakeup(struct pms_object *obj);

typedef enum {
	PMS_GLOBAL_STANDBY = 0x0,
	PMS_GLOBAL_MEMSTANDBY,
	PMS_GLOBAL_HIBERNATION,
	PMS_GLOBAL_MEMHIBERNATION
} pms_standby_t;

int pms_global_standby(pms_standby_t state);

/*
 * PMS Api based on LPC feature
 */
#ifdef CONFIG_STM_LPC
int pms_set_wakeup_timers(unsigned long long second);
#else
static inline int pms_set_wakeup_timers(unsigned long long second)
{
	return 0;
}
#endif
static inline int pms_disable_wakeup_timers(void)
{
	return pms_set_wakeup_timers(0);
}

static inline int pms_change_wakeup_timers(unsigned long long second)
{
	pms_set_wakeup_timers(0);
	return pms_set_wakeup_timers(second);
}
#endif
