#include <argp.h>
#include <stdbool.h>
#include <stdlib.h>

const char *argp_program_version = "LinBack v0.0.1";
static char doc[] = "Linux backdoor with autostart configuring";
static char args_doc[] = "[FILENAME]...";
static struct argp_option options[] = { 
    { "port", 'p', 0, 0, "Compare lines instead of characters."},
    { "disable-autostart", 'd', 0, 0, "Disable installing in autostart"},
    { "autostart-info", 'i', 0, 0, "Info about installing in autostart techniques"},
    { 0 }
};

struct arguments {
    enum { CHARACTER_MODE, WORD_MODE, LINE_MODE } mode;
    bool isCaseInsensitive;
};

static error_t parse_opt(int key, char *arg, struct argp_state *state) {
    struct arguments *arguments = state->input;
    switch (key) {
    case 'l': arguments->mode = LINE_MODE; break;
    case 'w': arguments->mode = WORD_MODE; break;
    case 'i': arguments->isCaseInsensitive = true; break;
    case ARGP_KEY_ARG: return 0;
    default: return ARGP_ERR_UNKNOWN;
    }   
    return 0;
}

static struct argp argp = { options, parse_opt, args_doc, doc, 0, 0, 0 };

int main(int argc, char *argv[]) {
    struct arguments arguments;

    arguments.mode = CHARACTER_MODE;
    arguments.isCaseInsensitive = false;

    argp_parse(&argp, argc, argv, 0, 0, &arguments);
    return EXIT_SUCCESS;
}
