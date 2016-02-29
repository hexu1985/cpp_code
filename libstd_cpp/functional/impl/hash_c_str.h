/*--- hash_c_str ----------------------------- Listing 3-2 ---------
 *	An adaptation of Peter Weinberger's (PJW) generic hashing
 *  algorithm based on Allen Holub's version.
 *
 *  Accepts a pointer to a datum to be hashed and returns an
 *  unsigned integer. This integer is called "calculated-key"
 *  in the text.
 *-------------------------------------------------------------*/
size_t hash_c_str(const char *datum);
