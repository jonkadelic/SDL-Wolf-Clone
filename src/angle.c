/******************************************************************************
 * Includes
 *****************************************************************************/
#include "angle.h"

/******************************************************************************
 * Defines
 *****************************************************************************/
#define MAX_ANGLE	360
#define MIN_ANGLE	0

/******************************************************************************
 * Local variables
 *****************************************************************************/
const FP	sinLookupTable[MAX_ANGLE] =
{
	0x0000, 0x0001, 0x0001, 0x0002, 0x0002, 0x0003, 0x0003, 0x0004, 0x0004, 0x0005, 
	0x0006, 0x0006, 0x0007, 0x0007, 0x0008, 0x0008, 0x0009, 0x0009, 0x000A, 0x000A, 
	0x000B, 0x000B, 0x000C, 0x000D, 0x000D, 0x000E, 0x000E, 0x000F, 0x000F, 0x0010, 
	0x0010, 0x0010, 0x0011, 0x0011, 0x0012, 0x0012, 0x0013, 0x0013, 0x0014, 0x0014, 
	0x0015, 0x0015, 0x0015, 0x0016, 0x0016, 0x0017, 0x0017, 0x0017, 0x0018, 0x0018, 
	0x0019, 0x0019, 0x0019, 0x001A, 0x001A, 0x001A, 0x001B, 0x001B, 0x001B, 0x001B, 
	0x001C, 0x001C, 0x001C, 0x001D, 0x001D, 0x001D, 0x001D, 0x001D, 0x001E, 0x001E, 
	0x001E, 0x001E, 0x001E, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 
	0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 
	0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 
	0x0020, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001E, 0x001E, 
	0x001E, 0x001E, 0x001E, 0x001D, 0x001D, 0x001D, 0x001D, 0x001D, 0x001C, 0x001C, 
	0x001C, 0x001B, 0x001B, 0x001B, 0x001B, 0x001A, 0x001A, 0x001A, 0x0019, 0x0019, 
	0x0019, 0x0018, 0x0018, 0x0017, 0x0017, 0x0017, 0x0016, 0x0016, 0x0015, 0x0015, 
	0x0015, 0x0014, 0x0014, 0x0013, 0x0013, 0x0012, 0x0012, 0x0011, 0x0011, 0x0010, 
	0x0010, 0x0010, 0x000F, 0x000F, 0x000E, 0x000E, 0x000D, 0x000D, 0x000C, 0x000B, 
	0x000B, 0x000A, 0x000A, 0x0009, 0x0009, 0x0008, 0x0008, 0x0007, 0x0007, 0x0006, 
	0x0006, 0x0005, 0x0004, 0x0004, 0x0003, 0x0003, 0x0002, 0x0002, 0x0001, 0x0001, 
	0x0000, 0x8001, 0x8001, 0x8002, 0x8002, 0x8003, 0x8003, 0x8004, 0x8004, 0x8005, 
	0x8006, 0x8006, 0x8007, 0x8007, 0x8008, 0x8008, 0x8009, 0x8009, 0x800A, 0x800A, 
	0x800B, 0x800B, 0x800C, 0x800D, 0x800D, 0x800E, 0x800E, 0x800F, 0x800F, 0x8010, 
	0x8010, 0x8010, 0x8011, 0x8011, 0x8012, 0x8012, 0x8013, 0x8013, 0x8014, 0x8014, 
	0x8015, 0x8015, 0x8015, 0x8016, 0x8016, 0x8017, 0x8017, 0x8017, 0x8018, 0x8018, 
	0x8019, 0x8019, 0x8019, 0x801A, 0x801A, 0x801A, 0x801B, 0x801B, 0x801B, 0x801B, 
	0x801C, 0x801C, 0x801C, 0x801D, 0x801D, 0x801D, 0x801D, 0x801D, 0x801E, 0x801E, 
	0x801E, 0x801E, 0x801E, 0x801F, 0x801F, 0x801F, 0x801F, 0x801F, 0x801F, 0x801F, 
	0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 
	0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 
	0x8020, 0x801F, 0x801F, 0x801F, 0x801F, 0x801F, 0x801F, 0x801F, 0x801E, 0x801E, 
	0x801E, 0x801E, 0x801E, 0x801D, 0x801D, 0x801D, 0x801D, 0x801D, 0x801C, 0x801C, 
	0x801C, 0x801B, 0x801B, 0x801B, 0x801B, 0x801A, 0x801A, 0x801A, 0x8019, 0x8019, 
	0x8019, 0x8018, 0x8018, 0x8017, 0x8017, 0x8017, 0x8016, 0x8016, 0x8015, 0x8015, 
	0x8015, 0x8014, 0x8014, 0x8013, 0x8013, 0x8012, 0x8012, 0x8011, 0x8011, 0x8010, 
	0x8010, 0x8010, 0x800F, 0x800F, 0x800E, 0x800E, 0x800D, 0x800D, 0x800C, 0x800B, 
	0x800B, 0x800A, 0x800A, 0x8009, 0x8009, 0x8008, 0x8008, 0x8007, 0x8007, 0x8006, 
	0x8006, 0x8005, 0x8004, 0x8004, 0x8003, 0x8003, 0x8002, 0x8002, 0x8001, 0x8001
};

const FP	cosLookupTable[MAX_ANGLE] =
{
	0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 
	0x0020, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001E, 0x001E, 
	0x001E, 0x001E, 0x001E, 0x001D, 0x001D, 0x001D, 0x001D, 0x001D, 0x001C, 0x001C, 
	0x001C, 0x001B, 0x001B, 0x001B, 0x001B, 0x001A, 0x001A, 0x001A, 0x0019, 0x0019, 
	0x0019, 0x0018, 0x0018, 0x0017, 0x0017, 0x0017, 0x0016, 0x0016, 0x0015, 0x0015, 
	0x0015, 0x0014, 0x0014, 0x0013, 0x0013, 0x0012, 0x0012, 0x0011, 0x0011, 0x0010, 
	0x0010, 0x0010, 0x000F, 0x000F, 0x000E, 0x000E, 0x000D, 0x000D, 0x000C, 0x000B, 
	0x000B, 0x000A, 0x000A, 0x0009, 0x0009, 0x0008, 0x0008, 0x0007, 0x0007, 0x0006, 
	0x0006, 0x0005, 0x0004, 0x0004, 0x0003, 0x0003, 0x0002, 0x0002, 0x0001, 0x0001, 
	0x0000, 0x8001, 0x8001, 0x8002, 0x8002, 0x8003, 0x8003, 0x8004, 0x8004, 0x8005, 
	0x8006, 0x8006, 0x8007, 0x8007, 0x8008, 0x8008, 0x8009, 0x8009, 0x800A, 0x800A, 
	0x800B, 0x800B, 0x800C, 0x800D, 0x800D, 0x800E, 0x800E, 0x800F, 0x800F, 0x8010, 
	0x8010, 0x8010, 0x8011, 0x8011, 0x8012, 0x8012, 0x8013, 0x8013, 0x8014, 0x8014, 
	0x8015, 0x8015, 0x8015, 0x8016, 0x8016, 0x8017, 0x8017, 0x8017, 0x8018, 0x8018, 
	0x8019, 0x8019, 0x8019, 0x801A, 0x801A, 0x801A, 0x801B, 0x801B, 0x801B, 0x801B, 
	0x801C, 0x801C, 0x801C, 0x801D, 0x801D, 0x801D, 0x801D, 0x801D, 0x801E, 0x801E, 
	0x801E, 0x801E, 0x801E, 0x801F, 0x801F, 0x801F, 0x801F, 0x801F, 0x801F, 0x801F, 
	0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 
	0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 0x8020, 
	0x8020, 0x801F, 0x801F, 0x801F, 0x801F, 0x801F, 0x801F, 0x801F, 0x801E, 0x801E, 
	0x801E, 0x801E, 0x801E, 0x801D, 0x801D, 0x801D, 0x801D, 0x801D, 0x801C, 0x801C, 
	0x801C, 0x801B, 0x801B, 0x801B, 0x801B, 0x801A, 0x801A, 0x801A, 0x8019, 0x8019, 
	0x8019, 0x8018, 0x8018, 0x8017, 0x8017, 0x8017, 0x8016, 0x8016, 0x8015, 0x8015, 
	0x8015, 0x8014, 0x8014, 0x8013, 0x8013, 0x8012, 0x8012, 0x8011, 0x8011, 0x8010, 
	0x8010, 0x8010, 0x800F, 0x800F, 0x800E, 0x800E, 0x800D, 0x800D, 0x800C, 0x800B, 
	0x800B, 0x800A, 0x800A, 0x8009, 0x8009, 0x8008, 0x8008, 0x8007, 0x8007, 0x8006, 
	0x8006, 0x8005, 0x8004, 0x8004, 0x8003, 0x8003, 0x8002, 0x8002, 0x8001, 0x8001, 
	0x0000, 0x0001, 0x0001, 0x0002, 0x0002, 0x0003, 0x0003, 0x0004, 0x0004, 0x0005, 
	0x0006, 0x0006, 0x0007, 0x0007, 0x0008, 0x0008, 0x0009, 0x0009, 0x000A, 0x000A, 
	0x000B, 0x000B, 0x000C, 0x000D, 0x000D, 0x000E, 0x000E, 0x000F, 0x000F, 0x0010, 
	0x0010, 0x0010, 0x0011, 0x0011, 0x0012, 0x0012, 0x0013, 0x0013, 0x0014, 0x0014, 
	0x0015, 0x0015, 0x0015, 0x0016, 0x0016, 0x0017, 0x0017, 0x0017, 0x0018, 0x0018, 
	0x0019, 0x0019, 0x0019, 0x001A, 0x001A, 0x001A, 0x001B, 0x001B, 0x001B, 0x001B, 
	0x001C, 0x001C, 0x001C, 0x001D, 0x001D, 0x001D, 0x001D, 0x001D, 0x001E, 0x001E, 
	0x001E, 0x001E, 0x001E, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 0x001F, 
	0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020, 0x0020
};

const FP	tanLookupTable[MAX_ANGLE] =
{
	0x0000, 0x0001, 0x0001, 0x0002, 0x0002, 0x0003, 0x0003, 0x0004, 0x0004, 0x0005, 
	0x0006, 0x0006, 0x0007, 0x0007, 0x0008, 0x0009, 0x0009, 0x000A, 0x000A, 0x000B, 
	0x000C, 0x000C, 0x000D, 0x000E, 0x000E, 0x000F, 0x0010, 0x0010, 0x0011, 0x0012, 
	0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0016, 0x0017, 0x0018, 0x0019, 0x001A, 
	0x001B, 0x001C, 0x001D, 0x001E, 0x001F, 0x0020, 0x0021, 0x0022, 0x0024, 0x0025, 
	0x0026, 0x0028, 0x0029, 0x002A, 0x002C, 0x002E, 0x002F, 0x0031, 0x0033, 0x0035, 
	0x0037, 0x003A, 0x003C, 0x003F, 0x0042, 0x0045, 0x0048, 0x004B, 0x004F, 0x0053, 
	0x0058, 0x005D, 0x0062, 0x0069, 0x0070, 0x0077, 0x0080, 0x008B, 0x0097, 0x00A5, 
	0x00B5, 0x00CA, 0x00E4, 0x0105, 0x0130, 0x016E, 0x01CA, 0x0263, 0x0394, 0x0729, 
	0x92C0, 0x8729, 0x8394, 0x8263, 0x81CA, 0x816E, 0x8130, 0x8105, 0x80E4, 0x80CA, 
	0x80B5, 0x80A5, 0x8097, 0x808B, 0x8080, 0x8077, 0x8070, 0x8069, 0x8062, 0x805D, 
	0x8058, 0x8053, 0x804F, 0x804B, 0x8048, 0x8045, 0x8042, 0x803F, 0x803C, 0x803A, 
	0x8037, 0x8035, 0x8033, 0x8031, 0x802F, 0x802E, 0x802C, 0x802A, 0x8029, 0x8028, 
	0x8026, 0x8025, 0x8024, 0x8022, 0x8021, 0x8020, 0x801F, 0x801E, 0x801D, 0x801C, 
	0x801B, 0x801A, 0x8019, 0x8018, 0x8017, 0x8016, 0x8016, 0x8015, 0x8014, 0x8013, 
	0x8012, 0x8012, 0x8011, 0x8010, 0x8010, 0x800F, 0x800E, 0x800E, 0x800D, 0x800C, 
	0x800C, 0x800B, 0x800A, 0x800A, 0x8009, 0x8009, 0x8008, 0x8007, 0x8007, 0x8006, 
	0x8006, 0x8005, 0x8004, 0x8004, 0x8003, 0x8003, 0x8002, 0x8002, 0x8001, 0x8001, 
	0x0000, 0x0001, 0x0001, 0x0002, 0x0002, 0x0003, 0x0003, 0x0004, 0x0004, 0x0005, 
	0x0006, 0x0006, 0x0007, 0x0007, 0x0008, 0x0009, 0x0009, 0x000A, 0x000A, 0x000B, 
	0x000C, 0x000C, 0x000D, 0x000E, 0x000E, 0x000F, 0x0010, 0x0010, 0x0011, 0x0012, 
	0x0012, 0x0013, 0x0014, 0x0015, 0x0016, 0x0016, 0x0017, 0x0018, 0x0019, 0x001A, 
	0x001B, 0x001C, 0x001D, 0x001E, 0x001F, 0x0020, 0x0021, 0x0022, 0x0024, 0x0025, 
	0x0026, 0x0028, 0x0029, 0x002A, 0x002C, 0x002E, 0x002F, 0x0031, 0x0033, 0x0035, 
	0x0037, 0x003A, 0x003C, 0x003F, 0x0042, 0x0045, 0x0048, 0x004B, 0x004F, 0x0053, 
	0x0058, 0x005D, 0x0062, 0x0069, 0x0070, 0x0077, 0x0080, 0x008B, 0x0097, 0x00A5, 
	0x00B5, 0x00CA, 0x00E4, 0x0105, 0x0130, 0x016E, 0x01CA, 0x0263, 0x0394, 0x0729, 
	0x8000, 0x8729, 0x8394, 0x8263, 0x81CA, 0x816E, 0x8130, 0x8105, 0x80E4, 0x80CA, 
	0x80B5, 0x80A5, 0x8097, 0x808B, 0x8080, 0x8077, 0x8070, 0x8069, 0x8062, 0x805D, 
	0x8058, 0x8053, 0x804F, 0x804B, 0x8048, 0x8045, 0x8042, 0x803F, 0x803C, 0x803A, 
	0x8037, 0x8035, 0x8033, 0x8031, 0x802F, 0x802E, 0x802C, 0x802A, 0x8029, 0x8028, 
	0x8026, 0x8025, 0x8024, 0x8022, 0x8021, 0x8020, 0x801F, 0x801E, 0x801D, 0x801C, 
	0x801B, 0x801A, 0x8019, 0x8018, 0x8017, 0x8016, 0x8016, 0x8015, 0x8014, 0x8013, 
	0x8012, 0x8012, 0x8011, 0x8010, 0x8010, 0x800F, 0x800E, 0x800E, 0x800D, 0x800C, 
	0x800C, 0x800B, 0x800A, 0x800A, 0x8009, 0x8009, 0x8008, 0x8007, 0x8007, 0x8006, 
	0x8006, 0x8005, 0x8004, 0x8004, 0x8003, 0x8003, 0x8002, 0x8002, 0x8001, 0x8001
};

/******************************************************************************
 * Function definitions
 *****************************************************************************/
ANGLE	Angle_Normalise
(
	ANGLE	angle
)
{
	while (angle >= MAX_ANGLE)
	{
		angle -= MAX_ANGLE;
	}

	return angle;
}

ANGLE	Angle_Add
(
	ANGLE	a,
	ANGLE	b
)
{
	return Angle_Normalise(a + b);
}

ANGLE	Angle_Sub
(
	ANGLE	a,
	ANGLE	b
)
{
	return Angle_Normalise(a - b);
}

FP	Angle_Sin
(
	ANGLE	angle
)
{
	return sinLookupTable[Angle_Normalise(angle)];
}

FP	Angle_Cos
(
	ANGLE	angle
)
{
	return cosLookupTable[Angle_Normalise(angle)];
}

FP	Angle_Tan
(
	ANGLE	angle
)
{
	return tanLookupTable[Angle_Normalise(angle)];
}