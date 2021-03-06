/* If we have 32-bit ints, pick off 3 bytes at a
 * time for as long as we can: */
while (srclen >= 3)
{
	/* Load string: */
	uint32_t str = *(uint32_t *)c;

	/* Reorder to 32-bit big-endian.
	 * The workset must be in big-endian, otherwise the shifted bits
	 * do not carry over properly among adjacent bytes: */
	str = __builtin_bswap32(str);

	/* Shift input by 6 bytes each round and mask in only the
	 * lower 6 bits; look up the character in the Base64 encoding
	 * table and write it to the output location: */
	*o++ = base64_table_enc[(str >> 26) & 0x3F];
	*o++ = base64_table_enc[(str >> 20) & 0x3F];
	*o++ = base64_table_enc[(str >> 14) & 0x3F];
	*o++ = base64_table_enc[(str >>  8) & 0x3F];

	c += 3;		/* 3 bytes of input  */
	outl += 4;	/* 4 bytes of output */
	srclen -= 3;
}
