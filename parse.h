struct environment;

struct parseoptions {
	_Bool dupbuilderr;
};

void parseinit(void);
void parse(struct environment *env);

extern struct parseoptions parseopts;

/* supported ninja version */
extern const char *ninjaversion;

/* default targets */
extern struct node **deftarg;
extern size_t ndeftarg;
