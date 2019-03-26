void
kmain(void)
{
	*((volatile char *)0xB8000) = 'H';
}
