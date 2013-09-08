<<<<<<< HEAD
#include "../../util.h"
#include "../browser.h"
#include "../helpline.h"
#include "../libslang.h"
#include "../ui.h"
#include "../util.h"
=======
#include "../browser.h"
#include "../helpline.h"
#include "../libslang.h"
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
#include "../../annotate.h"
#include "../../hist.h"
#include "../../sort.h"
#include "../../symbol.h"
#include <pthread.h>
<<<<<<< HEAD
#include <newt.h>
=======

static void ui__error_window(const char *fmt, ...)
{
	va_list ap;

	va_start(ap, fmt);
	newtWinMessagev((char *)"Error", (char *)"Ok", (char *)fmt, ap);
	va_end(ap);
}
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip

struct annotate_browser {
	struct ui_browser b;
	struct rb_root	  entries;
	struct rb_node	  *curr_hot;
<<<<<<< HEAD
	struct objdump_line *selection;
	int		    nr_asm_entries;
	int		    nr_entries;
	bool		    hide_src_code;
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
};

struct objdump_line_rb_node {
	struct rb_node	rb_node;
	double		percent;
	u32		idx;
<<<<<<< HEAD
	int		idx_asm;
=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
};

static inline
struct objdump_line_rb_node *objdump_line__rb(struct objdump_line *self)
{
	return (struct objdump_line_rb_node *)(self + 1);
}

<<<<<<< HEAD
static bool objdump_line__filter(struct ui_browser *browser, void *entry)
{
	struct annotate_browser *ab = container_of(browser, struct annotate_browser, b);

	if (ab->hide_src_code) {
		struct objdump_line *ol = list_entry(entry, struct objdump_line, node);
		return ol->offset == -1;
	}

	return false;
}

static void annotate_browser__write(struct ui_browser *self, void *entry, int row)
{
	struct annotate_browser *ab = container_of(self, struct annotate_browser, b);
	struct objdump_line *ol = list_entry(entry, struct objdump_line, node);
=======
static void annotate_browser__write(struct ui_browser *self, void *entry, int row)
{
	struct objdump_line *ol = rb_entry(entry, struct objdump_line, node);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	bool current_entry = ui_browser__is_current_entry(self, row);
	int width = self->width;

	if (ol->offset != -1) {
		struct objdump_line_rb_node *olrb = objdump_line__rb(ol);
		ui_browser__set_percent_color(self, olrb->percent, current_entry);
		slsmg_printf(" %7.2f ", olrb->percent);
	} else {
		ui_browser__set_percent_color(self, 0, current_entry);
		slsmg_write_nstring(" ", 9);
	}

	SLsmg_write_char(':');
	slsmg_write_nstring(" ", 8);
<<<<<<< HEAD

	/* The scroll bar isn't being used */
	if (!self->navkeypressed)
		width += 1;

	if (!ab->hide_src_code && ol->offset != -1)
		if (!current_entry || (self->use_navkeypressed &&
				       !self->navkeypressed))
			ui_browser__set_color(self, HE_COLORSET_CODE);

=======
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	if (!*ol->line)
		slsmg_write_nstring(" ", width - 18);
	else
		slsmg_write_nstring(ol->line, width - 18);

<<<<<<< HEAD
	if (current_entry)
		ab->selection = ol;
=======
	if (!current_entry)
		ui_browser__set_color(self, HE_COLORSET_CODE);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
}

static double objdump_line__calc_percent(struct objdump_line *self,
					 struct symbol *sym, int evidx)
{
	double percent = 0.0;

	if (self->offset != -1) {
		int len = sym->end - sym->start;
		unsigned int hits = 0;
		struct annotation *notes = symbol__annotation(sym);
		struct source_line *src_line = notes->src->lines;
		struct sym_hist *h = annotation__histogram(notes, evidx);
		s64 offset = self->offset;
		struct objdump_line *next;

		next = objdump__get_next_ip_line(&notes->src->source, self);
		while (offset < (s64)len &&
		       (next == NULL || offset < next->offset)) {
			if (src_line) {
				percent += src_line[offset].percent;
			} else
				hits += h->addr[offset];

			++offset;
		}
		/*
 		 * If the percentage wasn't already calculated in
 		 * symbol__get_source_line, do it now:
 		 */
		if (src_line == NULL && h->sum)
			percent = 100.0 * hits / h->sum;
	}

	return percent;
}

static void objdump__insert_line(struct rb_root *self,
				 struct objdump_line_rb_node *line)
{
	struct rb_node **p = &self->rb_node;
	struct rb_node *parent = NULL;
	struct objdump_line_rb_node *l;

	while (*p != NULL) {
		parent = *p;
		l = rb_entry(parent, struct objdump_line_rb_node, rb_node);
		if (line->percent < l->percent)
			p = &(*p)->rb_left;
		else
			p = &(*p)->rb_right;
	}
	rb_link_node(&line->rb_node, parent, p);
	rb_insert_color(&line->rb_node, self);
}

static void annotate_browser__set_top(struct annotate_browser *self,
				      struct rb_node *nd)
{
	struct objdump_line_rb_node *rbpos;
	struct objdump_line *pos;
	unsigned back;

	ui_browser__refresh_dimensions(&self->b);
	back = self->b.height / 2;
	rbpos = rb_entry(nd, struct objdump_line_rb_node, rb_node);
	pos = ((struct objdump_line *)rbpos) - 1;
	self->b.top_idx = self->b.index = rbpos->idx;

	while (self->b.top_idx != 0 && back != 0) {
		pos = list_entry(pos->node.prev, struct objdump_line, node);

		--self->b.top_idx;
		--back;
	}

	self->b.top = pos;
	self->curr_hot = nd;
}

static void annotate_browser__calc_percent(struct annotate_browser *browser,
					   int evidx)
{
<<<<<<< HEAD
	struct map_symbol *ms = browser->b.priv;
	struct symbol *sym = ms->sym;
=======
	struct symbol *sym = browser->b.priv;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	struct annotation *notes = symbol__annotation(sym);
	struct objdump_line *pos;

	browser->entries = RB_ROOT;

	pthread_mutex_lock(&notes->lock);

	list_for_each_entry(pos, &notes->src->source, node) {
		struct objdump_line_rb_node *rbpos = objdump_line__rb(pos);
		rbpos->percent = objdump_line__calc_percent(pos, sym, evidx);
		if (rbpos->percent < 0.01) {
			RB_CLEAR_NODE(&rbpos->rb_node);
			continue;
		}
		objdump__insert_line(&browser->entries, rbpos);
	}
	pthread_mutex_unlock(&notes->lock);

	browser->curr_hot = rb_last(&browser->entries);
}

<<<<<<< HEAD
static bool annotate_browser__toggle_source(struct annotate_browser *browser)
{
	struct objdump_line *ol;
	struct objdump_line_rb_node *olrb;
	off_t offset = browser->b.index - browser->b.top_idx;

	browser->b.seek(&browser->b, offset, SEEK_CUR);
	ol = list_entry(browser->b.top, struct objdump_line, node);
	olrb = objdump_line__rb(ol);

	if (browser->hide_src_code) {
		if (olrb->idx_asm < offset)
			offset = olrb->idx;

		browser->b.nr_entries = browser->nr_entries;
		browser->hide_src_code = false;
		browser->b.seek(&browser->b, -offset, SEEK_CUR);
		browser->b.top_idx = olrb->idx - offset;
		browser->b.index = olrb->idx;
	} else {
		if (olrb->idx_asm < 0) {
			ui_helpline__puts("Only available for assembly lines.");
			browser->b.seek(&browser->b, -offset, SEEK_CUR);
			return false;
		}

		if (olrb->idx_asm < offset)
			offset = olrb->idx_asm;

		browser->b.nr_entries = browser->nr_asm_entries;
		browser->hide_src_code = true;
		browser->b.seek(&browser->b, -offset, SEEK_CUR);
		browser->b.top_idx = olrb->idx_asm - offset;
		browser->b.index = olrb->idx_asm;
	}

	return true;
}

static int annotate_browser__run(struct annotate_browser *self, int evidx,
				 void(*timer)(void *arg),
				 void *arg, int delay_secs)
{
	struct rb_node *nd = NULL;
	struct map_symbol *ms = self->b.priv;
	struct symbol *sym = ms->sym;
	const char *help = "<-/ESC: Exit, TAB/shift+TAB: Cycle hot lines, "
			   "H: Go to hottest line, ->/ENTER: Line action, "
			   "S: Toggle source code view";
	int key;

	if (ui_browser__show(&self->b, sym->name, help) < 0)
		return -1;

=======
static int annotate_browser__run(struct annotate_browser *self, int evidx,
				 int refresh)
{
	struct rb_node *nd = NULL;
	struct symbol *sym = self->b.priv;
	/*
	 * RIGHT To allow builtin-annotate to cycle thru multiple symbols by
	 * examining the exit key for this function.
	 */
	int exit_keys[] = { 'H', NEWT_KEY_TAB, NEWT_KEY_UNTAB,
			    NEWT_KEY_RIGHT, 0 };
	int key;

	if (ui_browser__show(&self->b, sym->name,
			     "<-, -> or ESC: exit, TAB/shift+TAB: "
			     "cycle hottest lines, H: Hottest") < 0)
		return -1;

	ui_browser__add_exit_keys(&self->b, exit_keys);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	annotate_browser__calc_percent(self, evidx);

	if (self->curr_hot)
		annotate_browser__set_top(self, self->curr_hot);

	nd = self->curr_hot;

<<<<<<< HEAD
	while (1) {
		key = ui_browser__run(&self->b, delay_secs);

		if (delay_secs != 0) {
=======
	if (refresh != 0)
		newtFormSetTimer(self->b.form, refresh);

	while (1) {
		key = ui_browser__run(&self->b);

		if (refresh != 0) {
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			annotate_browser__calc_percent(self, evidx);
			/*
			 * Current line focus got out of the list of most active
			 * lines, NULL it so that if TAB|UNTAB is pressed, we
			 * move to curr_hot (current hottest line).
			 */
			if (nd != NULL && RB_EMPTY_NODE(nd))
				nd = NULL;
		}

		switch (key) {
<<<<<<< HEAD
		case K_TIMER:
			if (timer != NULL)
				timer(arg);

			if (delay_secs != 0)
				symbol__annotate_decay_histogram(sym, evidx);
			continue;
		case K_TAB:
=======
		case -1:
			/*
 			 * FIXME we need to check if it was
 			 * es.reason == NEWT_EXIT_TIMER
 			 */
			if (refresh != 0)
				symbol__annotate_decay_histogram(sym, evidx);
			continue;
		case NEWT_KEY_TAB:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			if (nd != NULL) {
				nd = rb_prev(nd);
				if (nd == NULL)
					nd = rb_last(&self->entries);
			} else
				nd = self->curr_hot;
			break;
<<<<<<< HEAD
		case K_UNTAB:
=======
		case NEWT_KEY_UNTAB:
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
			if (nd != NULL)
				nd = rb_next(nd);
				if (nd == NULL)
					nd = rb_first(&self->entries);
			else
				nd = self->curr_hot;
			break;
		case 'H':
<<<<<<< HEAD
		case 'h':
			nd = self->curr_hot;
			break;
		case 'S':
		case 's':
			if (annotate_browser__toggle_source(self))
				ui_helpline__puts(help);
			continue;
		case K_ENTER:
		case K_RIGHT:
			if (self->selection == NULL) {
				ui_helpline__puts("Huh? No selection. Report to linux-kernel@vger.kernel.org");
				continue;
			}

			if (self->selection->offset == -1) {
				ui_helpline__puts("Actions are only available for assembly lines.");
				continue;
			} else {
				char *s = strstr(self->selection->line, "callq ");
				struct annotation *notes;
				struct symbol *target;
				u64 ip;

				if (s == NULL) {
					ui_helpline__puts("Actions are only available for the 'callq' instruction.");
					continue;
				}

				s = strchr(s, ' ');
				if (s++ == NULL) {
					ui_helpline__puts("Invallid callq instruction.");
					continue;
				}

				ip = strtoull(s, NULL, 16);
				ip = ms->map->map_ip(ms->map, ip);
				target = map__find_symbol(ms->map, ip, NULL);
				if (target == NULL) {
					ui_helpline__puts("The called function was not found.");
					continue;
				}

				notes = symbol__annotation(target);
				pthread_mutex_lock(&notes->lock);

				if (notes->src == NULL && symbol__alloc_hist(target) < 0) {
					pthread_mutex_unlock(&notes->lock);
					ui__warning("Not enough memory for annotating '%s' symbol!\n",
						    target->name);
					continue;
				}

				pthread_mutex_unlock(&notes->lock);
				symbol__tui_annotate(target, ms->map, evidx,
						     timer, arg, delay_secs);
				ui_browser__show_title(&self->b, sym->name);
			}
			continue;
		case K_LEFT:
		case K_ESC:
		case 'q':
		case CTRL('c'):
			goto out;
		default:
			continue;
=======
			nd = self->curr_hot;
			break;
		default:
			goto out;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		}

		if (nd != NULL)
			annotate_browser__set_top(self, nd);
	}
out:
	ui_browser__hide(&self->b);
	return key;
}

<<<<<<< HEAD
int hist_entry__tui_annotate(struct hist_entry *he, int evidx,
			     void(*timer)(void *arg), void *arg, int delay_secs)
{
	return symbol__tui_annotate(he->ms.sym, he->ms.map, evidx,
				    timer, arg, delay_secs);
}

int symbol__tui_annotate(struct symbol *sym, struct map *map, int evidx,
			 void(*timer)(void *arg), void *arg,
			 int delay_secs)
{
	struct objdump_line *pos, *n;
	struct annotation *notes;
	struct map_symbol ms = {
		.map = map,
		.sym = sym,
	};
=======
int hist_entry__tui_annotate(struct hist_entry *he, int evidx)
{
	return symbol__tui_annotate(he->ms.sym, he->ms.map, evidx, 0);
}

int symbol__tui_annotate(struct symbol *sym, struct map *map, int evidx,
			 int refresh)
{
	struct objdump_line *pos, *n;
	struct annotation *notes;
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	struct annotate_browser browser = {
		.b = {
			.refresh = ui_browser__list_head_refresh,
			.seek	 = ui_browser__list_head_seek,
			.write	 = annotate_browser__write,
<<<<<<< HEAD
			.filter  = objdump_line__filter,
			.priv	 = &ms,
			.use_navkeypressed = true,
=======
			.priv	 = sym,
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		},
	};
	int ret;

	if (sym == NULL)
		return -1;

	if (map->dso->annotate_warned)
		return -1;

	if (symbol__annotate(sym, map, sizeof(struct objdump_line_rb_node)) < 0) {
<<<<<<< HEAD
		ui__error("%s", ui_helpline__last_msg);
=======
		ui__error_window(ui_helpline__last_msg);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
		return -1;
	}

	ui_helpline__push("Press <- or ESC to exit");

	notes = symbol__annotation(sym);

	list_for_each_entry(pos, &notes->src->source, node) {
		struct objdump_line_rb_node *rbpos;
		size_t line_len = strlen(pos->line);

		if (browser.b.width < line_len)
			browser.b.width = line_len;
		rbpos = objdump_line__rb(pos);
<<<<<<< HEAD
		rbpos->idx = browser.nr_entries++;
		if (pos->offset != -1)
			rbpos->idx_asm = browser.nr_asm_entries++;
		else
			rbpos->idx_asm = -1;
	}

	browser.b.nr_entries = browser.nr_entries;
	browser.b.entries = &notes->src->source,
	browser.b.width += 18; /* Percentage */
	ret = annotate_browser__run(&browser, evidx, timer, arg, delay_secs);
=======
		rbpos->idx = browser.b.nr_entries++;
	}

	browser.b.entries = &notes->src->source,
	browser.b.width += 18; /* Percentage */
	ret = annotate_browser__run(&browser, evidx, refresh);
>>>>>>> f37bb4a... Initial commit from GT-I9105P_JB_Opensource.zip
	list_for_each_entry_safe(pos, n, &notes->src->source, node) {
		list_del(&pos->node);
		objdump_line__free(pos);
	}
	return ret;
}
