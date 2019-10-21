#ifndef _MISSINGTHREADLOCALEINFO

typedef struct localerefcount {
	char *locale;
	wchar_t *wlocale;
	int *refcount;
	int *wrefcount;
} locrefcount;

struct __crt_locale_data {
        int refcount;
        unsigned int lc_codepage;
        unsigned int lc_collate_cp;
        unsigned int lc_time_cp;
        locrefcount lc_category[6];
        int lc_clike;
        int mb_cur_max;
        int * lconv_intl_refcount;
        int * lconv_num_refcount;
        int * lconv_mon_refcount;
        struct lconv * lconv;
        int * ctype1_refcount;
        unsigned short * ctype1;
        const unsigned short * pctype;
        const unsigned char * pclmap;
        const unsigned char * pcumap;
        struct __lc_time_data * lc_time_curr;
        wchar_t * locale_name[6];
};

#define _MISSINGTHREADLOCALEINFO

#endif  /* _THREADLOCALEINFO */
