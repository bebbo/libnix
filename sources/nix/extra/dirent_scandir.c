#include <dirent.h>
#include <stdlib.h>
#include <string.h>

int scandir(const char *dirname,struct dirent ***namelist,
	int (*select)(const struct dirent *),
	int (*dcomp)(const struct dirent **, const struct dirent **))
{
	register struct dirent *d, *p, **names;
	register size_t nitems;
	long arraysz;
	DIR *dirp;
	int successful = 0;
	int rc = 0;
	
	dirp = NULL;
	names = NULL;
	nitems = 0;
	
	if ((dirp = opendir(dirname)) == NULL)
		return(-1);
	
	/*
	 * estimate the array size.
	 */
	arraysz = 16;
	names = (struct dirent **)malloc(arraysz * sizeof(struct dirent *));
	if (names == NULL)
		goto cleanup;
	
	while ((d = readdir(dirp)) != NULL) {
		if (select != NULL && !(*select)(d))
			continue;	/* just selected names */
		/*
		 * Make a minimum size copy of the data
		 */
		p = (struct dirent *)malloc(sizeof(struct dirent));
		if (p == NULL)
			goto cleanup;
		p->d_fileno = d->d_fileno;
		p->d_reclen = d->d_reclen;
		p->d_namlen = d->d_namlen;
		bcopy(d->d_name, p->d_name, p->d_namlen + 1);
		/*
		 * Check to make sure the array has space left and
		 * realloc the maximum size.
		 */
		if (nitems == arraysz) {
			void *n = realloc((char *)names,
				(arraysz+=16) * sizeof(struct dirent *));
			if (n == NULL)
				goto cleanup;
			names = (struct dirent **)n;
		}
		names[nitems++] = p;
	}
	successful = 1;
cleanup:
	closedir(dirp);
	if (successful) {
		if (nitems && dcomp != NULL)
			qsort(names, nitems, sizeof(struct dirent *), (void *)dcomp);
		*namelist = names;
		rc = nitems;
	} else {  /* We were unsuccessful, clean up storage and return -1.  */
		if ( names ) {
			int i;
			for (i=0; i < nitems; i++ )
				free( names[i] );
			free( names );
		}
		rc = -1;
	}
	
	return(rc);
}

/*
 * Alphabetic order comparison routine for those who want it.
 */
int alphasort(const struct dirent **d1,const struct dirent **d2)
{
  return(strcmp((*d1)->d_name, (*d2)->d_name));
}
