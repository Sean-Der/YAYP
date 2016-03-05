#ifndef ERROR_H
#define ERROR_H

#define y4m_error(...) \
	fprintf(stderr, __VA_ARGS__); \
	fprintf(stderr, " %s:%d\n", __FILE__, __LINE__);

#endif
