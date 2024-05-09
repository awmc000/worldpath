/*
 * January 2nd, 2024
 *
 * world.c
 *
 * Graph of all countries in the world that have one or more
 * land borders with another country.
 */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <nds.h>
#include <filesystem.h>
#include <nf_lib.h>
#include "../include/world.h"
#include "../include/hash_table.h"
#include "../include/graph.h"


// Image data gen. by GRIT
// #include "world_map.h"

#define BUFFERSIZE 127
#define HLINE "+------------------------------+"

#define ERASENEWLINE(buffer) buffer[strcspn(buffer, "\n")] = '\0'

// Globals
// Pannable map on top of the screen
int camera_x = 0, camera_y = 0;

enum GAME_STATE 
{
	GENERATING,
	PLAYING,
	MAIN_MENU,
	GAME_END,
	WAITING,
	PANNING
};

struct Vertex * select_country(struct hash_table * name_to_alpha2,
	struct hash_table * alpha2_to_numeric,
	struct Vertex ** countryVertices)
{
	int done_selecting = 0;
	char * linebuf, * alpha2;
	while (!done_selecting)
	{
		printf("\nEnter COUNTRY NAME or 'done':");
		// Allocate buffer
		linebuf = calloc(BUFFERSIZE, sizeof(char));
		
		// Get user input
		fgets(linebuf, BUFFERSIZE * sizeof(char), stdin);
		
		// fgets() is capturing the newline, set it to a null byte
		ERASENEWLINE(linebuf);
		
		if (strcmp(linebuf, "done") == 0)
			return NULL;

		// Get the alpha2 code of the name
		if (hashtable_contains(name_to_alpha2, linebuf))
		{
			alpha2 = dictionary_get_value(name_to_alpha2, linebuf);
			printf("Country \"%s\" has the Alpha2 code %s.\n", linebuf, alpha2);
			done_selecting = 1;
		}
		else
		{
			fprintf(stdout, "Did not find \"%s\" as a country name.\n", linebuf);
		}
	}
	
	// Get the country code number of the alpha2
	char * s_number = dictionary_get_value(alpha2_to_numeric, alpha2);
	
	// Represent that number as a numeric type
	int number = atoi(s_number);
	
	// fetch that vertex from the array
	struct Vertex * selected_country = countryVertices[number];
	free(linebuf);

	// Flush the buffer so no input is carried over.
	fflush(stdin);
	return selected_country;
}

struct Path * user_enter_path(struct hash_table * name_to_alpha2,
	struct hash_table * alpha2_to_numeric,
	struct Vertex ** countryVertices,
	struct Vertex * source)
{
	char * linebuf = calloc(BUFFERSIZE, sizeof(char));

	struct Path * user_path = construct_path();
	// path_insert(user_path, source->s_data);
	do 
	{
		// Select a country
		struct Vertex * next_country = select_country(name_to_alpha2,
			alpha2_to_numeric, countryVertices);
		// Add it to the path
		if (next_country != NULL)
			path_insert(user_path, next_country->s_data);
		else
			break;
	} while (strcmp(linebuf, "done") != 0);

	path_print(user_path);
	return user_path;
}

int score_path(struct Path * sys_path, struct Path * user_path)
{
	// Scoring system: 10 points for a valid path
	// -1 for every length over sys path
	// +100 for every length under sys path (should never happen)!	
	int score = 0;

	int diff = sys_path->length - user_path->length;
	if (diff > 0)
		score -= diff;
	else
		score += (100 * diff);

	return score;
}

struct Vertex * random_country(struct Vertex **countryVertices)
{
	struct Vertex * vert = NULL;

	while (vert == NULL)
	{
		vert = countryVertices[rand() % 896];
	}

	// printf("Settled on %s.\n", vert->s_data);

	return vert;
}

void OnKeyPressed(int key) {
	if(key > 0)
    	iprintf("%c", key);
}

void create_country_strings()
{
	AF_name = strdup("Afghanistan");
	AL_name = strdup("Albania");
	DZ_name = strdup("Algeria");
	AD_name = strdup("Andorra");
	AO_name = strdup("Angola");
	AR_name = strdup("Argentina");
	AM_name = strdup("Armenia");
	AT_name = strdup("Austria");
	AZ_name = strdup("Azerbaijan");
	BD_name = strdup("Bangladesh");
	BY_name = strdup("Belarus");
	BE_name = strdup("Belgium");
	BZ_name = strdup("Belize");
	BJ_name = strdup("Benin");
	BT_name = strdup("Bhutan");
	BO_name = strdup("Bolivia (Plurinational State of)");
	BA_name = strdup("Bosnia and Herzegovina");
	BW_name = strdup("Botswana");
	BR_name = strdup("Brazil");
	BN_name = strdup("Brunei Darussalam");
	BG_name = strdup("Bulgaria");
	BF_name = strdup("Burkina Faso");
	BI_name = strdup("Burundi");
	KH_name = strdup("Cambodia");
	CM_name = strdup("Cameroon");
	CA_name = strdup("Canada");
	CF_name = strdup("Central African Republic");
	TD_name = strdup("Chad");
	CL_name = strdup("Chile");
	CN_name = strdup("China");
	CO_name = strdup("Colombia");
	CG_name = strdup("Congo");
	CD_name = strdup("Democratic Republic of Congo");
	CR_name = strdup("Costa Rica");
	CI_name = strdup("Cote d'Ivoire");
	HR_name = strdup("Croatia");
	CZ_name = strdup("Czechia");
	DK_name = strdup("Denmark");
	DJ_name = strdup("Djibouti");
	DO_name = strdup("Dominican Republic");
	EC_name = strdup("Ecuador");
	EG_name = strdup("Egypt");
	SV_name = strdup("El Salvador");
	GQ_name = strdup("Equatorial Guinea");
	ER_name = strdup("Eritrea");
	EE_name = strdup("Estonia");
	SZ_name = strdup("Eswatini");
	ET_name = strdup("Ethiopia");
	FI_name = strdup("Finland");
	FR_name = strdup("France");
	GF_name = strdup("French Guiana");
	GA_name = strdup("Gabon");
	GM_name = strdup("Gambia");
	GE_name = strdup("Georgia");
	DE_name = strdup("Germany");
	GH_name = strdup("Ghana");
	GI_name = strdup("Gibraltar");
	GR_name = strdup("Greece");
	GT_name = strdup("Guatemala");
	GN_name = strdup("Guinea");
	GW_name = strdup("Guinea-Bissau");
	GY_name = strdup("Guyana");
	HT_name = strdup("Haiti");
	VA_name = strdup("Holy See");
	HN_name = strdup("Honduras");
	HK_name = strdup("Hong Kong");
	HU_name = strdup("Hungary");
	IN_name = strdup("India");
	ID_name = strdup("Indonesia");
	IR_name = strdup("Iran");
	IQ_name = strdup("Iraq");
	IE_name = strdup("Ireland");
	IL_name = strdup("Israel");
	IT_name = strdup("Italy");
	JO_name = strdup("Jordan");
	KZ_name = strdup("Kazakhstan");
	KE_name = strdup("Kenya");
	KP_name = strdup("North Korea");
	KR_name = strdup("Republic of Korea");
	KW_name = strdup("Kuwait");
	KG_name = strdup("Kyrgyzstan");
	LA_name = strdup("Lao People's Democratic Republic");
	LV_name = strdup("Latvia");
	LB_name = strdup("Lebanon");
	LS_name = strdup("Lesotho");
	LR_name = strdup("Liberia");
	LY_name = strdup("Libya");
	LI_name = strdup("Liechtenstein");
	LT_name = strdup("Lithuania");
	LU_name = strdup("Luxembourg");
	MO_name = strdup("Macao");
	MW_name = strdup("Malawi");
	MY_name = strdup("Malaysia");
	ML_name = strdup("Mali");
	MR_name = strdup("Mauritania");
	MX_name = strdup("Mexico");
	MD_name = strdup("Moldova");
	MC_name = strdup("Monaco");
	MN_name = strdup("Mongolia");
	ME_name = strdup("Montenegro");
	MA_name = strdup("Morocco");
	MZ_name = strdup("Mozambique");
	MM_name = strdup("Myanmar");
	NA_name = strdup("Namibia");
	NP_name = strdup("Nepal");
	NL_name = strdup("Netherlands");
	NI_name = strdup("Nicaragua");
	NE_name = strdup("Niger");
	NG_name = strdup("Nigeria");
	MK_name = strdup("North Macedonia");
	NO_name = strdup("Norway");
	OM_name = strdup("Oman");
	PK_name = strdup("Pakistan");
	PS_name = strdup("Palestine");
	PA_name = strdup("Panama");
	PG_name = strdup("Papua New Guinea");
	PY_name = strdup("Paraguay");
	PE_name = strdup("Peru");
	PL_name = strdup("Poland");
	PT_name = strdup("Portugal");
	QA_name = strdup("Qatar");
	RO_name = strdup("Romania");
	RU_name = strdup("Russian Federation");
	RW_name = strdup("Rwanda");
	MF_name = strdup("Saint Martin (French part)");
	SM_name = strdup("San Marino");
	SA_name = strdup("Saudi Arabia");
	SN_name = strdup("Senegal");
	RS_name = strdup("Serbia");
	SL_name = strdup("Sierra Leone");
	SX_name = strdup("Sint Maarten (Dutch part)");
	SK_name = strdup("Slovakia");
	SI_name = strdup("Slovenia");
	SO_name = strdup("Somalia");
	ZA_name = strdup("South Africa");
	SS_name = strdup("South Sudan");
	ES_name = strdup("Spain");
	SD_name = strdup("Sudan");
	SR_name = strdup("Suriname");
	SE_name = strdup("Sweden");
	CH_name = strdup("Switzerland");
	SY_name = strdup("Syrian Arab Republic");
	TW_name = strdup("Taiwan");
	TJ_name = strdup("Tajikistan");
	TZ_name = strdup("Tanzania");
	TH_name = strdup("Thailand");
	TL_name = strdup("Timor-Leste");
	TG_name = strdup("Togo");
	TN_name = strdup("Tunisia");
	TR_name = strdup("Turkey");
	TM_name = strdup("Turkmenistan");
	UG_name = strdup("Uganda");
	UA_name = strdup("Ukraine");
	AE_name = strdup("United Arab Emirates");
	GB_name = strdup("United Kingdom of Great Britain and Northern Ireland");
	US_name = strdup("United States of America");
	UM_name = strdup("United States Minor Outlying Islands");
	UY_name = strdup("Uruguay");
	UZ_name = strdup("Uzbekistan");
	VE_name = strdup("Venezuela (Bolivarian Republic of)");
	VN_name = strdup("Viet Nam");
	EH_name = strdup("Western Sahara");
	YE_name = strdup("Yemen");
	ZM_name = strdup("Zambia");
	ZW_name = strdup("Zimbabwe");
	AF_alpha2 = strdup("AF");
	AL_alpha2 = strdup("AL");
	DZ_alpha2 = strdup("DZ");
	AD_alpha2 = strdup("AD");
	AO_alpha2 = strdup("AO");
	AR_alpha2 = strdup("AR");
	AM_alpha2 = strdup("AM");
	AT_alpha2 = strdup("AT");
	AZ_alpha2 = strdup("AZ");
	BD_alpha2 = strdup("BD");
	BY_alpha2 = strdup("BY");
	BE_alpha2 = strdup("BE");
	BZ_alpha2 = strdup("BZ");
	BJ_alpha2 = strdup("BJ");
	BT_alpha2 = strdup("BT");
	BO_alpha2 = strdup("BO");
	BA_alpha2 = strdup("BA");
	BW_alpha2 = strdup("BW");
	BR_alpha2 = strdup("BR");
	BN_alpha2 = strdup("BN");
	BG_alpha2 = strdup("BG");
	BF_alpha2 = strdup("BF");
	BI_alpha2 = strdup("BI");
	KH_alpha2 = strdup("KH");
	CM_alpha2 = strdup("CM");
	CA_alpha2 = strdup("CA");
	CF_alpha2 = strdup("CF");
	TD_alpha2 = strdup("TD");
	CL_alpha2 = strdup("CL");
	CN_alpha2 = strdup("CN");
	CO_alpha2 = strdup("CO");
	CG_alpha2 = strdup("CG");
	CD_alpha2 = strdup("CD");
	CR_alpha2 = strdup("CR");
	CI_alpha2 = strdup("CI");
	HR_alpha2 = strdup("HR");
	CZ_alpha2 = strdup("CZ");
	DK_alpha2 = strdup("DK");
	DJ_alpha2 = strdup("DJ");
	DO_alpha2 = strdup("DO");
	EC_alpha2 = strdup("EC");
	EG_alpha2 = strdup("EG");
	SV_alpha2 = strdup("SV");
	GQ_alpha2 = strdup("GQ");
	ER_alpha2 = strdup("ER");
	EE_alpha2 = strdup("EE");
	SZ_alpha2 = strdup("SZ");
	ET_alpha2 = strdup("ET");
	FI_alpha2 = strdup("FI");
	FR_alpha2 = strdup("FR");
	GF_alpha2 = strdup("GF");
	GA_alpha2 = strdup("GA");
	GM_alpha2 = strdup("GM");
	GE_alpha2 = strdup("GE");
	DE_alpha2 = strdup("DE");
	GH_alpha2 = strdup("GH");
	GI_alpha2 = strdup("GI");
	GR_alpha2 = strdup("GR");
	GT_alpha2 = strdup("GT");
	GN_alpha2 = strdup("GN");
	GW_alpha2 = strdup("GW");
	GY_alpha2 = strdup("GY");
	HT_alpha2 = strdup("HT");
	VA_alpha2 = strdup("VA");
	HN_alpha2 = strdup("HN");
	HK_alpha2 = strdup("HK");
	HU_alpha2 = strdup("HU");
	IN_alpha2 = strdup("IN");
	ID_alpha2 = strdup("ID");
	IR_alpha2 = strdup("IR");
	IQ_alpha2 = strdup("IQ");
	IE_alpha2 = strdup("IE");
	IL_alpha2 = strdup("IL");
	IT_alpha2 = strdup("IT");
	JO_alpha2 = strdup("JO");
	KZ_alpha2 = strdup("KZ");
	KE_alpha2 = strdup("KE");
	KP_alpha2 = strdup("KP");
	KR_alpha2 = strdup("KR");
	KW_alpha2 = strdup("KW");
	KG_alpha2 = strdup("KG");
	LA_alpha2 = strdup("LA");
	LV_alpha2 = strdup("LV");
	LB_alpha2 = strdup("LB");
	LS_alpha2 = strdup("LS");
	LR_alpha2 = strdup("LR");
	LY_alpha2 = strdup("LY");
	LI_alpha2 = strdup("LI");
	LT_alpha2 = strdup("LT");
	LU_alpha2 = strdup("LU");
	MO_alpha2 = strdup("MO");
	MW_alpha2 = strdup("MW");
	MY_alpha2 = strdup("MY");
	ML_alpha2 = strdup("ML");
	MR_alpha2 = strdup("MR");
	MX_alpha2 = strdup("MX");
	MD_alpha2 = strdup("MD");
	MC_alpha2 = strdup("MC");
	MN_alpha2 = strdup("MN");
	ME_alpha2 = strdup("ME");
	MA_alpha2 = strdup("MA");
	MZ_alpha2 = strdup("MZ");
	MM_alpha2 = strdup("MM");
	NA_alpha2 = strdup("NA");
	NP_alpha2 = strdup("NP");
	NL_alpha2 = strdup("NL");
	NI_alpha2 = strdup("NI");
	NE_alpha2 = strdup("NE");
	NG_alpha2 = strdup("NG");
	MK_alpha2 = strdup("MK");
	NO_alpha2 = strdup("NO");
	OM_alpha2 = strdup("OM");
	PK_alpha2 = strdup("PK");
	PS_alpha2 = strdup("PS");
	PA_alpha2 = strdup("PA");
	PG_alpha2 = strdup("PG");
	PY_alpha2 = strdup("PY");
	PE_alpha2 = strdup("PE");
	PL_alpha2 = strdup("PL");
	PT_alpha2 = strdup("PT");
	QA_alpha2 = strdup("QA");
	RO_alpha2 = strdup("RO");
	RU_alpha2 = strdup("RU");
	RW_alpha2 = strdup("RW");
	MF_alpha2 = strdup("MF");
	SM_alpha2 = strdup("SM");
	SA_alpha2 = strdup("SA");
	SN_alpha2 = strdup("SN");
	RS_alpha2 = strdup("RS");
	SL_alpha2 = strdup("SL");
	SX_alpha2 = strdup("SX");
	SK_alpha2 = strdup("SK");
	SI_alpha2 = strdup("SI");
	SO_alpha2 = strdup("SO");
	ZA_alpha2 = strdup("ZA");
	SS_alpha2 = strdup("SS");
	ES_alpha2 = strdup("ES");
	SD_alpha2 = strdup("SD");
	SR_alpha2 = strdup("SR");
	SE_alpha2 = strdup("SE");
	CH_alpha2 = strdup("CH");
	SY_alpha2 = strdup("SY");
	TW_alpha2 = strdup("TW");
	TJ_alpha2 = strdup("TJ");
	TZ_alpha2 = strdup("TZ");
	TH_alpha2 = strdup("TH");
	TL_alpha2 = strdup("TL");
	TG_alpha2 = strdup("TG");
	TN_alpha2 = strdup("TN");
	TR_alpha2 = strdup("TR");
	TM_alpha2 = strdup("TM");
	UG_alpha2 = strdup("UG");
	UA_alpha2 = strdup("UA");
	AE_alpha2 = strdup("AE");
	GB_alpha2 = strdup("GB");
	US_alpha2 = strdup("US");
	UM_alpha2 = strdup("UM");
	UY_alpha2 = strdup("UY");
	UZ_alpha2 = strdup("UZ");
	VE_alpha2 = strdup("VE");
	VN_alpha2 = strdup("VN");
	EH_alpha2 = strdup("EH");
	YE_alpha2 = strdup("YE");
	ZM_alpha2 = strdup("ZM");
	ZW_alpha2 = strdup("ZW");
}

void populate_dictionaries(struct hash_table * alpha2_to_name, 
	struct hash_table *name_to_alpha2,
	struct hash_table *alpha2_to_numeric)
{
	dictionary_insert(alpha2_to_name, AF_alpha2, AF_name);
	dictionary_insert(alpha2_to_name, AL_alpha2, AL_name);
	dictionary_insert(alpha2_to_name, DZ_alpha2, DZ_name);
	dictionary_insert(alpha2_to_name, AD_alpha2, AD_name);
	dictionary_insert(alpha2_to_name, AO_alpha2, AO_name);
	dictionary_insert(alpha2_to_name, AR_alpha2, AR_name);
	dictionary_insert(alpha2_to_name, AM_alpha2, AM_name);
	dictionary_insert(alpha2_to_name, AT_alpha2, AT_name);
	dictionary_insert(alpha2_to_name, AZ_alpha2, AZ_name);
	dictionary_insert(alpha2_to_name, BD_alpha2, BD_name);
	dictionary_insert(alpha2_to_name, BY_alpha2, BY_name);
	dictionary_insert(alpha2_to_name, BE_alpha2, BE_name);
	dictionary_insert(alpha2_to_name, BZ_alpha2, BZ_name);
	dictionary_insert(alpha2_to_name, BJ_alpha2, BJ_name);
	dictionary_insert(alpha2_to_name, BT_alpha2, BT_name);
	dictionary_insert(alpha2_to_name, BO_alpha2, BO_name);
	dictionary_insert(alpha2_to_name, BA_alpha2, BA_name);
	dictionary_insert(alpha2_to_name, BW_alpha2, BW_name);
	dictionary_insert(alpha2_to_name, BR_alpha2, BR_name);
	dictionary_insert(alpha2_to_name, BN_alpha2, BN_name);
	dictionary_insert(alpha2_to_name, BG_alpha2, BG_name);
	dictionary_insert(alpha2_to_name, BF_alpha2, BF_name);
	dictionary_insert(alpha2_to_name, BI_alpha2, BI_name);
	dictionary_insert(alpha2_to_name, KH_alpha2, KH_name);
	dictionary_insert(alpha2_to_name, CM_alpha2, CM_name);
	dictionary_insert(alpha2_to_name, CA_alpha2, CA_name);
	dictionary_insert(alpha2_to_name, CF_alpha2, CF_name);
	dictionary_insert(alpha2_to_name, TD_alpha2, TD_name);
	dictionary_insert(alpha2_to_name, CL_alpha2, CL_name);
	dictionary_insert(alpha2_to_name, CN_alpha2, CN_name);
	dictionary_insert(alpha2_to_name, CO_alpha2, CO_name);
	dictionary_insert(alpha2_to_name, CG_alpha2, CG_name);
	dictionary_insert(alpha2_to_name, CD_alpha2, CD_name);
	dictionary_insert(alpha2_to_name, CR_alpha2, CR_name);
	dictionary_insert(alpha2_to_name, CI_alpha2, CI_name);
	dictionary_insert(alpha2_to_name, HR_alpha2, HR_name);
	dictionary_insert(alpha2_to_name, CZ_alpha2, CZ_name);
	dictionary_insert(alpha2_to_name, DK_alpha2, DK_name);
	dictionary_insert(alpha2_to_name, DJ_alpha2, DJ_name);
	dictionary_insert(alpha2_to_name, DO_alpha2, DO_name);
	dictionary_insert(alpha2_to_name, EC_alpha2, EC_name);
	dictionary_insert(alpha2_to_name, EG_alpha2, EG_name);
	dictionary_insert(alpha2_to_name, SV_alpha2, SV_name);
	dictionary_insert(alpha2_to_name, GQ_alpha2, GQ_name);
	dictionary_insert(alpha2_to_name, ER_alpha2, ER_name);
	dictionary_insert(alpha2_to_name, EE_alpha2, EE_name);
	dictionary_insert(alpha2_to_name, SZ_alpha2, SZ_name);
	dictionary_insert(alpha2_to_name, ET_alpha2, ET_name);
	dictionary_insert(alpha2_to_name, FI_alpha2, FI_name);
	dictionary_insert(alpha2_to_name, FR_alpha2, FR_name);
	dictionary_insert(alpha2_to_name, GF_alpha2, GF_name);
	dictionary_insert(alpha2_to_name, GA_alpha2, GA_name);
	dictionary_insert(alpha2_to_name, GM_alpha2, GM_name);
	dictionary_insert(alpha2_to_name, GE_alpha2, GE_name);
	dictionary_insert(alpha2_to_name, DE_alpha2, DE_name);
	dictionary_insert(alpha2_to_name, GH_alpha2, GH_name);
	dictionary_insert(alpha2_to_name, GI_alpha2, GI_name);
	dictionary_insert(alpha2_to_name, GR_alpha2, GR_name);
	dictionary_insert(alpha2_to_name, GT_alpha2, GT_name);
	dictionary_insert(alpha2_to_name, GN_alpha2, GN_name);
	dictionary_insert(alpha2_to_name, GW_alpha2, GW_name);
	dictionary_insert(alpha2_to_name, GY_alpha2, GY_name);
	dictionary_insert(alpha2_to_name, HT_alpha2, HT_name);
	dictionary_insert(alpha2_to_name, VA_alpha2, VA_name);
	dictionary_insert(alpha2_to_name, HN_alpha2, HN_name);
	dictionary_insert(alpha2_to_name, HK_alpha2, HK_name);
	dictionary_insert(alpha2_to_name, HU_alpha2, HU_name);
	dictionary_insert(alpha2_to_name, IN_alpha2, IN_name);
	dictionary_insert(alpha2_to_name, ID_alpha2, ID_name);
	dictionary_insert(alpha2_to_name, IR_alpha2, IR_name);
	dictionary_insert(alpha2_to_name, IQ_alpha2, IQ_name);
	dictionary_insert(alpha2_to_name, IE_alpha2, IE_name);
	dictionary_insert(alpha2_to_name, IL_alpha2, IL_name);
	dictionary_insert(alpha2_to_name, IT_alpha2, IT_name);
	dictionary_insert(alpha2_to_name, JO_alpha2, JO_name);
	dictionary_insert(alpha2_to_name, KZ_alpha2, KZ_name);
	dictionary_insert(alpha2_to_name, KE_alpha2, KE_name);
	dictionary_insert(alpha2_to_name, KP_alpha2, KP_name);
	dictionary_insert(alpha2_to_name, KR_alpha2, KR_name);
	dictionary_insert(alpha2_to_name, KW_alpha2, KW_name);
	dictionary_insert(alpha2_to_name, KG_alpha2, KG_name);
	dictionary_insert(alpha2_to_name, LA_alpha2, LA_name);
	dictionary_insert(alpha2_to_name, LV_alpha2, LV_name);
	dictionary_insert(alpha2_to_name, LB_alpha2, LB_name);
	dictionary_insert(alpha2_to_name, LS_alpha2, LS_name);
	dictionary_insert(alpha2_to_name, LR_alpha2, LR_name);
	dictionary_insert(alpha2_to_name, LY_alpha2, LY_name);
	dictionary_insert(alpha2_to_name, LI_alpha2, LI_name);
	dictionary_insert(alpha2_to_name, LT_alpha2, LT_name);
	dictionary_insert(alpha2_to_name, LU_alpha2, LU_name);
	dictionary_insert(alpha2_to_name, MO_alpha2, MO_name);
	dictionary_insert(alpha2_to_name, MW_alpha2, MW_name);
	dictionary_insert(alpha2_to_name, MY_alpha2, MY_name);
	dictionary_insert(alpha2_to_name, ML_alpha2, ML_name);
	dictionary_insert(alpha2_to_name, MR_alpha2, MR_name);
	dictionary_insert(alpha2_to_name, MX_alpha2, MX_name);
	dictionary_insert(alpha2_to_name, MD_alpha2, MD_name);
	dictionary_insert(alpha2_to_name, MC_alpha2, MC_name);
	dictionary_insert(alpha2_to_name, MN_alpha2, MN_name);
	dictionary_insert(alpha2_to_name, ME_alpha2, ME_name);
	dictionary_insert(alpha2_to_name, MA_alpha2, MA_name);
	dictionary_insert(alpha2_to_name, MZ_alpha2, MZ_name);
	dictionary_insert(alpha2_to_name, MM_alpha2, MM_name);
	dictionary_insert(alpha2_to_name, NA_alpha2, NA_name);
	dictionary_insert(alpha2_to_name, NP_alpha2, NP_name);
	dictionary_insert(alpha2_to_name, NL_alpha2, NL_name);
	dictionary_insert(alpha2_to_name, NI_alpha2, NI_name);
	dictionary_insert(alpha2_to_name, NE_alpha2, NE_name);
	dictionary_insert(alpha2_to_name, NG_alpha2, NG_name);
	dictionary_insert(alpha2_to_name, MK_alpha2, MK_name);
	dictionary_insert(alpha2_to_name, NO_alpha2, NO_name);
	dictionary_insert(alpha2_to_name, OM_alpha2, OM_name);
	dictionary_insert(alpha2_to_name, PK_alpha2, PK_name);
	dictionary_insert(alpha2_to_name, PS_alpha2, PS_name);
	dictionary_insert(alpha2_to_name, PA_alpha2, PA_name);
	dictionary_insert(alpha2_to_name, PG_alpha2, PG_name);
	dictionary_insert(alpha2_to_name, PY_alpha2, PY_name);
	dictionary_insert(alpha2_to_name, PE_alpha2, PE_name);
	dictionary_insert(alpha2_to_name, PL_alpha2, PL_name);
	dictionary_insert(alpha2_to_name, PT_alpha2, PT_name);
	dictionary_insert(alpha2_to_name, QA_alpha2, QA_name);
	dictionary_insert(alpha2_to_name, RO_alpha2, RO_name);
	dictionary_insert(alpha2_to_name, RU_alpha2, RU_name);
	dictionary_insert(alpha2_to_name, RW_alpha2, RW_name);
	dictionary_insert(alpha2_to_name, MF_alpha2, MF_name);
	dictionary_insert(alpha2_to_name, SM_alpha2, SM_name);
	dictionary_insert(alpha2_to_name, SA_alpha2, SA_name);
	dictionary_insert(alpha2_to_name, SN_alpha2, SN_name);
	dictionary_insert(alpha2_to_name, RS_alpha2, RS_name);
	dictionary_insert(alpha2_to_name, SL_alpha2, SL_name);
	dictionary_insert(alpha2_to_name, SX_alpha2, SX_name);
	dictionary_insert(alpha2_to_name, SK_alpha2, SK_name);
	dictionary_insert(alpha2_to_name, SI_alpha2, SI_name);
	dictionary_insert(alpha2_to_name, SO_alpha2, SO_name);
	dictionary_insert(alpha2_to_name, ZA_alpha2, ZA_name);
	dictionary_insert(alpha2_to_name, SS_alpha2, SS_name);
	dictionary_insert(alpha2_to_name, ES_alpha2, ES_name);
	dictionary_insert(alpha2_to_name, SD_alpha2, SD_name);
	dictionary_insert(alpha2_to_name, SR_alpha2, SR_name);
	dictionary_insert(alpha2_to_name, SE_alpha2, SE_name);
	dictionary_insert(alpha2_to_name, CH_alpha2, CH_name);
	dictionary_insert(alpha2_to_name, SY_alpha2, SY_name);
	dictionary_insert(alpha2_to_name, TW_alpha2, TW_name);
	dictionary_insert(alpha2_to_name, TJ_alpha2, TJ_name);
	dictionary_insert(alpha2_to_name, TZ_alpha2, TZ_name);
	dictionary_insert(alpha2_to_name, TH_alpha2, TH_name);
	dictionary_insert(alpha2_to_name, TL_alpha2, TL_name);
	dictionary_insert(alpha2_to_name, TG_alpha2, TG_name);
	dictionary_insert(alpha2_to_name, TN_alpha2, TN_name);
	dictionary_insert(alpha2_to_name, TR_alpha2, TR_name);
	dictionary_insert(alpha2_to_name, TM_alpha2, TM_name);
	dictionary_insert(alpha2_to_name, UG_alpha2, UG_name);
	dictionary_insert(alpha2_to_name, UA_alpha2, UA_name);
	dictionary_insert(alpha2_to_name, AE_alpha2, AE_name);
	dictionary_insert(alpha2_to_name, GB_alpha2, GB_name);
	dictionary_insert(alpha2_to_name, US_alpha2, US_name);
	dictionary_insert(alpha2_to_name, UM_alpha2, UM_name);
	dictionary_insert(alpha2_to_name, UY_alpha2, UY_name);
	dictionary_insert(alpha2_to_name, UZ_alpha2, UZ_name);
	dictionary_insert(alpha2_to_name, VE_alpha2, VE_name);
	dictionary_insert(alpha2_to_name, VN_alpha2, VN_name);
	dictionary_insert(alpha2_to_name, EH_alpha2, EH_name);
	dictionary_insert(alpha2_to_name, YE_alpha2, YE_name);
	dictionary_insert(alpha2_to_name, ZM_alpha2, ZM_name);
	dictionary_insert(alpha2_to_name, ZW_alpha2, ZW_name);
	dictionary_insert(name_to_alpha2, AF_name, AF_alpha2);
	dictionary_insert(name_to_alpha2, AL_name, AL_alpha2);
	dictionary_insert(name_to_alpha2, DZ_name, DZ_alpha2);
	dictionary_insert(name_to_alpha2, AD_name, AD_alpha2);
	dictionary_insert(name_to_alpha2, AO_name, AO_alpha2);
	dictionary_insert(name_to_alpha2, AR_name, AR_alpha2);
	dictionary_insert(name_to_alpha2, AM_name, AM_alpha2);
	dictionary_insert(name_to_alpha2, AT_name, AT_alpha2);
	dictionary_insert(name_to_alpha2, AZ_name, AZ_alpha2);
	dictionary_insert(name_to_alpha2, BD_name, BD_alpha2);
	dictionary_insert(name_to_alpha2, BY_name, BY_alpha2);
	dictionary_insert(name_to_alpha2, BE_name, BE_alpha2);
	dictionary_insert(name_to_alpha2, BZ_name, BZ_alpha2);
	dictionary_insert(name_to_alpha2, BJ_name, BJ_alpha2);
	dictionary_insert(name_to_alpha2, BT_name, BT_alpha2);
	dictionary_insert(name_to_alpha2, BO_name, BO_alpha2);
	dictionary_insert(name_to_alpha2, BA_name, BA_alpha2);
	dictionary_insert(name_to_alpha2, BW_name, BW_alpha2);
	dictionary_insert(name_to_alpha2, BR_name, BR_alpha2);
	dictionary_insert(name_to_alpha2, BN_name, BN_alpha2);
	dictionary_insert(name_to_alpha2, BG_name, BG_alpha2);
	dictionary_insert(name_to_alpha2, BF_name, BF_alpha2);
	dictionary_insert(name_to_alpha2, BI_name, BI_alpha2);
	dictionary_insert(name_to_alpha2, KH_name, KH_alpha2);
	dictionary_insert(name_to_alpha2, CM_name, CM_alpha2);
	dictionary_insert(name_to_alpha2, CA_name, CA_alpha2);
	dictionary_insert(name_to_alpha2, CF_name, CF_alpha2);
	dictionary_insert(name_to_alpha2, TD_name, TD_alpha2);
	dictionary_insert(name_to_alpha2, CL_name, CL_alpha2);
	dictionary_insert(name_to_alpha2, CN_name, CN_alpha2);
	dictionary_insert(name_to_alpha2, CO_name, CO_alpha2);
	dictionary_insert(name_to_alpha2, CG_name, CG_alpha2);
	dictionary_insert(name_to_alpha2, CD_name, CD_alpha2);
	dictionary_insert(name_to_alpha2, CR_name, CR_alpha2);
	dictionary_insert(name_to_alpha2, CI_name, CI_alpha2);
	dictionary_insert(name_to_alpha2, HR_name, HR_alpha2);
	dictionary_insert(name_to_alpha2, CZ_name, CZ_alpha2);
	dictionary_insert(name_to_alpha2, DK_name, DK_alpha2);
	dictionary_insert(name_to_alpha2, DJ_name, DJ_alpha2);
	dictionary_insert(name_to_alpha2, DO_name, DO_alpha2);
	dictionary_insert(name_to_alpha2, EC_name, EC_alpha2);
	dictionary_insert(name_to_alpha2, EG_name, EG_alpha2);
	dictionary_insert(name_to_alpha2, SV_name, SV_alpha2);
	dictionary_insert(name_to_alpha2, GQ_name, GQ_alpha2);
	dictionary_insert(name_to_alpha2, ER_name, ER_alpha2);
	dictionary_insert(name_to_alpha2, EE_name, EE_alpha2);
	dictionary_insert(name_to_alpha2, SZ_name, SZ_alpha2);
	dictionary_insert(name_to_alpha2, ET_name, ET_alpha2);
	dictionary_insert(name_to_alpha2, FI_name, FI_alpha2);
	dictionary_insert(name_to_alpha2, FR_name, FR_alpha2);
	dictionary_insert(name_to_alpha2, GF_name, GF_alpha2);
	dictionary_insert(name_to_alpha2, GA_name, GA_alpha2);
	dictionary_insert(name_to_alpha2, GM_name, GM_alpha2);
	dictionary_insert(name_to_alpha2, GE_name, GE_alpha2);
	dictionary_insert(name_to_alpha2, DE_name, DE_alpha2);
	dictionary_insert(name_to_alpha2, GH_name, GH_alpha2);
	dictionary_insert(name_to_alpha2, GI_name, GI_alpha2);
	dictionary_insert(name_to_alpha2, GR_name, GR_alpha2);
	dictionary_insert(name_to_alpha2, GT_name, GT_alpha2);
	dictionary_insert(name_to_alpha2, GN_name, GN_alpha2);
	dictionary_insert(name_to_alpha2, GW_name, GW_alpha2);
	dictionary_insert(name_to_alpha2, GY_name, GY_alpha2);
	dictionary_insert(name_to_alpha2, HT_name, HT_alpha2);
	dictionary_insert(name_to_alpha2, VA_name, VA_alpha2);
	dictionary_insert(name_to_alpha2, HN_name, HN_alpha2);
	dictionary_insert(name_to_alpha2, HK_name, HK_alpha2);
	dictionary_insert(name_to_alpha2, HU_name, HU_alpha2);
	dictionary_insert(name_to_alpha2, IN_name, IN_alpha2);
	dictionary_insert(name_to_alpha2, ID_name, ID_alpha2);
	dictionary_insert(name_to_alpha2, IR_name, IR_alpha2);
	dictionary_insert(name_to_alpha2, IQ_name, IQ_alpha2);
	dictionary_insert(name_to_alpha2, IE_name, IE_alpha2);
	dictionary_insert(name_to_alpha2, IL_name, IL_alpha2);
	dictionary_insert(name_to_alpha2, IT_name, IT_alpha2);
	dictionary_insert(name_to_alpha2, JO_name, JO_alpha2);
	dictionary_insert(name_to_alpha2, KZ_name, KZ_alpha2);
	dictionary_insert(name_to_alpha2, KE_name, KE_alpha2);
	dictionary_insert(name_to_alpha2, KP_name, KP_alpha2);
	dictionary_insert(name_to_alpha2, KR_name, KR_alpha2);
	dictionary_insert(name_to_alpha2, KW_name, KW_alpha2);
	dictionary_insert(name_to_alpha2, KG_name, KG_alpha2);
	dictionary_insert(name_to_alpha2, LA_name, LA_alpha2);
	dictionary_insert(name_to_alpha2, LV_name, LV_alpha2);
	dictionary_insert(name_to_alpha2, LB_name, LB_alpha2);
	dictionary_insert(name_to_alpha2, LS_name, LS_alpha2);
	dictionary_insert(name_to_alpha2, LR_name, LR_alpha2);
	dictionary_insert(name_to_alpha2, LY_name, LY_alpha2);
	dictionary_insert(name_to_alpha2, LI_name, LI_alpha2);
	dictionary_insert(name_to_alpha2, LT_name, LT_alpha2);
	dictionary_insert(name_to_alpha2, LU_name, LU_alpha2);
	dictionary_insert(name_to_alpha2, MO_name, MO_alpha2);
	dictionary_insert(name_to_alpha2, MW_name, MW_alpha2);
	dictionary_insert(name_to_alpha2, MY_name, MY_alpha2);
	dictionary_insert(name_to_alpha2, ML_name, ML_alpha2);
	dictionary_insert(name_to_alpha2, MR_name, MR_alpha2);
	dictionary_insert(name_to_alpha2, MX_name, MX_alpha2);
	dictionary_insert(name_to_alpha2, MD_name, MD_alpha2);
	dictionary_insert(name_to_alpha2, MC_name, MC_alpha2);
	dictionary_insert(name_to_alpha2, MN_name, MN_alpha2);
	dictionary_insert(name_to_alpha2, ME_name, ME_alpha2);
	dictionary_insert(name_to_alpha2, MA_name, MA_alpha2);
	dictionary_insert(name_to_alpha2, MZ_name, MZ_alpha2);
	dictionary_insert(name_to_alpha2, MM_name, MM_alpha2);
	dictionary_insert(name_to_alpha2, NA_name, NA_alpha2);
	dictionary_insert(name_to_alpha2, NP_name, NP_alpha2);
	dictionary_insert(name_to_alpha2, NL_name, NL_alpha2);
	dictionary_insert(name_to_alpha2, NI_name, NI_alpha2);
	dictionary_insert(name_to_alpha2, NE_name, NE_alpha2);
	dictionary_insert(name_to_alpha2, NG_name, NG_alpha2);
	dictionary_insert(name_to_alpha2, MK_name, MK_alpha2);
	dictionary_insert(name_to_alpha2, NO_name, NO_alpha2);
	dictionary_insert(name_to_alpha2, OM_name, OM_alpha2);
	dictionary_insert(name_to_alpha2, PK_name, PK_alpha2);
	dictionary_insert(name_to_alpha2, PS_name, PS_alpha2);
	dictionary_insert(name_to_alpha2, PA_name, PA_alpha2);
	dictionary_insert(name_to_alpha2, PG_name, PG_alpha2);
	dictionary_insert(name_to_alpha2, PY_name, PY_alpha2);
	dictionary_insert(name_to_alpha2, PE_name, PE_alpha2);
	dictionary_insert(name_to_alpha2, PL_name, PL_alpha2);
	dictionary_insert(name_to_alpha2, PT_name, PT_alpha2);
	dictionary_insert(name_to_alpha2, QA_name, QA_alpha2);
	dictionary_insert(name_to_alpha2, RO_name, RO_alpha2);
	dictionary_insert(name_to_alpha2, RU_name, RU_alpha2);
	dictionary_insert(name_to_alpha2, RW_name, RW_alpha2);
	dictionary_insert(name_to_alpha2, MF_name, MF_alpha2);
	dictionary_insert(name_to_alpha2, SM_name, SM_alpha2);
	dictionary_insert(name_to_alpha2, SA_name, SA_alpha2);
	dictionary_insert(name_to_alpha2, SN_name, SN_alpha2);
	dictionary_insert(name_to_alpha2, RS_name, RS_alpha2);
	dictionary_insert(name_to_alpha2, SL_name, SL_alpha2);
	dictionary_insert(name_to_alpha2, SX_name, SX_alpha2);
	dictionary_insert(name_to_alpha2, SK_name, SK_alpha2);
	dictionary_insert(name_to_alpha2, SI_name, SI_alpha2);
	dictionary_insert(name_to_alpha2, SO_name, SO_alpha2);
	dictionary_insert(name_to_alpha2, ZA_name, ZA_alpha2);
	dictionary_insert(name_to_alpha2, SS_name, SS_alpha2);
	dictionary_insert(name_to_alpha2, ES_name, ES_alpha2);
	dictionary_insert(name_to_alpha2, SD_name, SD_alpha2);
	dictionary_insert(name_to_alpha2, SR_name, SR_alpha2);
	dictionary_insert(name_to_alpha2, SE_name, SE_alpha2);
	dictionary_insert(name_to_alpha2, CH_name, CH_alpha2);
	dictionary_insert(name_to_alpha2, SY_name, SY_alpha2);
	dictionary_insert(name_to_alpha2, TW_name, TW_alpha2);
	dictionary_insert(name_to_alpha2, TJ_name, TJ_alpha2);
	dictionary_insert(name_to_alpha2, TZ_name, TZ_alpha2);
	dictionary_insert(name_to_alpha2, TH_name, TH_alpha2);
	dictionary_insert(name_to_alpha2, TL_name, TL_alpha2);
	dictionary_insert(name_to_alpha2, TG_name, TG_alpha2);
	dictionary_insert(name_to_alpha2, TN_name, TN_alpha2);
	dictionary_insert(name_to_alpha2, TR_name, TR_alpha2);
	dictionary_insert(name_to_alpha2, TM_name, TM_alpha2);
	dictionary_insert(name_to_alpha2, UG_name, UG_alpha2);
	dictionary_insert(name_to_alpha2, UA_name, UA_alpha2);
	dictionary_insert(name_to_alpha2, AE_name, AE_alpha2);
	dictionary_insert(name_to_alpha2, GB_name, GB_alpha2);
	dictionary_insert(name_to_alpha2, US_name, US_alpha2);
	dictionary_insert(name_to_alpha2, UM_name, UM_alpha2);
	dictionary_insert(name_to_alpha2, UY_name, UY_alpha2);
	dictionary_insert(name_to_alpha2, UZ_name, UZ_alpha2);
	dictionary_insert(name_to_alpha2, VE_name, VE_alpha2);
	dictionary_insert(name_to_alpha2, VN_name, VN_alpha2);
	dictionary_insert(name_to_alpha2, EH_name, EH_alpha2);
	dictionary_insert(name_to_alpha2, YE_name, YE_alpha2);
	dictionary_insert(name_to_alpha2, ZM_name, ZM_alpha2);
	dictionary_insert(name_to_alpha2, ZW_name, ZW_alpha2);
	dictionary_insert(alpha2_to_numeric, "AF", "4");
	dictionary_insert(alpha2_to_numeric, "AL", "8");
	dictionary_insert(alpha2_to_numeric, "DZ", "12");
	dictionary_insert(alpha2_to_numeric, "AD", "20");
	dictionary_insert(alpha2_to_numeric, "AO", "24");
	dictionary_insert(alpha2_to_numeric, "AR", "32");
	dictionary_insert(alpha2_to_numeric, "AM", "51");
	dictionary_insert(alpha2_to_numeric, "AT", "40");
	dictionary_insert(alpha2_to_numeric, "AZ", "31");
	dictionary_insert(alpha2_to_numeric, "BD", "50");
	dictionary_insert(alpha2_to_numeric, "BY", "112");
	dictionary_insert(alpha2_to_numeric, "BE", "56");
	dictionary_insert(alpha2_to_numeric, "BZ", "84");
	dictionary_insert(alpha2_to_numeric, "BJ", "204");
	dictionary_insert(alpha2_to_numeric, "BT", "64");
	dictionary_insert(alpha2_to_numeric, "BO", "68");
	dictionary_insert(alpha2_to_numeric, "BA", "70");
	dictionary_insert(alpha2_to_numeric, "BW", "72");
	dictionary_insert(alpha2_to_numeric, "BR", "76");
	dictionary_insert(alpha2_to_numeric, "BN", "96");
	dictionary_insert(alpha2_to_numeric, "BG", "100");
	dictionary_insert(alpha2_to_numeric, "BF", "854");
	dictionary_insert(alpha2_to_numeric, "BI", "108");
	dictionary_insert(alpha2_to_numeric, "KH", "116");
	dictionary_insert(alpha2_to_numeric, "CM", "120");
	dictionary_insert(alpha2_to_numeric, "CA", "124");
	dictionary_insert(alpha2_to_numeric, "CF", "140");
	dictionary_insert(alpha2_to_numeric, "TD", "148");
	dictionary_insert(alpha2_to_numeric, "CL", "152");
	dictionary_insert(alpha2_to_numeric, "CN", "156");
	dictionary_insert(alpha2_to_numeric, "CO", "170");
	dictionary_insert(alpha2_to_numeric, "CG", "178");
	dictionary_insert(alpha2_to_numeric, "CD", "180");
	dictionary_insert(alpha2_to_numeric, "CR", "188");
	dictionary_insert(alpha2_to_numeric, "CI", "384");
	dictionary_insert(alpha2_to_numeric, "HR", "191");
	dictionary_insert(alpha2_to_numeric, "CZ", "203");
	dictionary_insert(alpha2_to_numeric, "DK", "208");
	dictionary_insert(alpha2_to_numeric, "DJ", "262");
	dictionary_insert(alpha2_to_numeric, "DO", "214");
	dictionary_insert(alpha2_to_numeric, "EC", "218");
	dictionary_insert(alpha2_to_numeric, "EG", "818");
	dictionary_insert(alpha2_to_numeric, "SV", "222");
	dictionary_insert(alpha2_to_numeric, "GQ", "226");
	dictionary_insert(alpha2_to_numeric, "ER", "232");
	dictionary_insert(alpha2_to_numeric, "EE", "233");
	dictionary_insert(alpha2_to_numeric, "SZ", "748");
	dictionary_insert(alpha2_to_numeric, "ET", "231");
	dictionary_insert(alpha2_to_numeric, "FI", "246");
	dictionary_insert(alpha2_to_numeric, "FR", "250");
	dictionary_insert(alpha2_to_numeric, "GF", "254");
	dictionary_insert(alpha2_to_numeric, "GA", "266");
	dictionary_insert(alpha2_to_numeric, "GM", "270");
	dictionary_insert(alpha2_to_numeric, "GE", "268");
	dictionary_insert(alpha2_to_numeric, "DE", "276");
	dictionary_insert(alpha2_to_numeric, "GH", "288");
	dictionary_insert(alpha2_to_numeric, "GI", "292");
	dictionary_insert(alpha2_to_numeric, "GR", "300");
	dictionary_insert(alpha2_to_numeric, "GT", "320");
	dictionary_insert(alpha2_to_numeric, "GN", "324");
	dictionary_insert(alpha2_to_numeric, "GW", "624");
	dictionary_insert(alpha2_to_numeric, "GY", "328");
	dictionary_insert(alpha2_to_numeric, "HT", "332");
	dictionary_insert(alpha2_to_numeric, "VA", "336");
	dictionary_insert(alpha2_to_numeric, "HN", "340");
	dictionary_insert(alpha2_to_numeric, "HK", "344");
	dictionary_insert(alpha2_to_numeric, "HU", "348");
	dictionary_insert(alpha2_to_numeric, "IN", "356");
	dictionary_insert(alpha2_to_numeric, "ID", "360");
	dictionary_insert(alpha2_to_numeric, "IR", "364");
	dictionary_insert(alpha2_to_numeric, "IQ", "368");
	dictionary_insert(alpha2_to_numeric, "IE", "372");
	dictionary_insert(alpha2_to_numeric, "IL", "376");
	dictionary_insert(alpha2_to_numeric, "IT", "380");
	dictionary_insert(alpha2_to_numeric, "JO", "400");
	dictionary_insert(alpha2_to_numeric, "KZ", "398");
	dictionary_insert(alpha2_to_numeric, "KE", "404");
	dictionary_insert(alpha2_to_numeric, "KP", "408");
	dictionary_insert(alpha2_to_numeric, "KR", "410");
	dictionary_insert(alpha2_to_numeric, "KW", "414");
	dictionary_insert(alpha2_to_numeric, "KG", "417");
	dictionary_insert(alpha2_to_numeric, "LA", "418");
	dictionary_insert(alpha2_to_numeric, "LV", "428");
	dictionary_insert(alpha2_to_numeric, "LB", "422");
	dictionary_insert(alpha2_to_numeric, "LS", "426");
	dictionary_insert(alpha2_to_numeric, "LR", "430");
	dictionary_insert(alpha2_to_numeric, "LY", "434");
	dictionary_insert(alpha2_to_numeric, "LI", "438");
	dictionary_insert(alpha2_to_numeric, "LT", "440");
	dictionary_insert(alpha2_to_numeric, "LU", "442");
	dictionary_insert(alpha2_to_numeric, "MO", "446");
	dictionary_insert(alpha2_to_numeric, "MW", "454");
	dictionary_insert(alpha2_to_numeric, "MY", "458");
	dictionary_insert(alpha2_to_numeric, "ML", "466");
	dictionary_insert(alpha2_to_numeric, "MR", "478");
	dictionary_insert(alpha2_to_numeric, "MX", "484");
	dictionary_insert(alpha2_to_numeric, "MD", "498");
	dictionary_insert(alpha2_to_numeric, "MC", "492");
	dictionary_insert(alpha2_to_numeric, "MN", "496");
	dictionary_insert(alpha2_to_numeric, "ME", "499");
	dictionary_insert(alpha2_to_numeric, "MA", "504");
	dictionary_insert(alpha2_to_numeric, "MZ", "508");
	dictionary_insert(alpha2_to_numeric, "MM", "104");
	dictionary_insert(alpha2_to_numeric, "NA", "516");
	dictionary_insert(alpha2_to_numeric, "NP", "524");
	dictionary_insert(alpha2_to_numeric, "NL", "528");
	dictionary_insert(alpha2_to_numeric, "NI", "558");
	dictionary_insert(alpha2_to_numeric, "NE", "562");
	dictionary_insert(alpha2_to_numeric, "NG", "566");
	dictionary_insert(alpha2_to_numeric, "MK", "807");
	dictionary_insert(alpha2_to_numeric, "NO", "578");
	dictionary_insert(alpha2_to_numeric, "OM", "512");
	dictionary_insert(alpha2_to_numeric, "PK", "586");
	dictionary_insert(alpha2_to_numeric, "PS", "275");
	dictionary_insert(alpha2_to_numeric, "PA", "591");
	dictionary_insert(alpha2_to_numeric, "PG", "598");
	dictionary_insert(alpha2_to_numeric, "PY", "600");
	dictionary_insert(alpha2_to_numeric, "PE", "604");
	dictionary_insert(alpha2_to_numeric, "PL", "616");
	dictionary_insert(alpha2_to_numeric, "PT", "620");
	dictionary_insert(alpha2_to_numeric, "QA", "634");
	dictionary_insert(alpha2_to_numeric, "RO", "642");
	dictionary_insert(alpha2_to_numeric, "RU", "643");
	dictionary_insert(alpha2_to_numeric, "RW", "646");
	dictionary_insert(alpha2_to_numeric, "MF", "663");
	dictionary_insert(alpha2_to_numeric, "SM", "674");
	dictionary_insert(alpha2_to_numeric, "SA", "682");
	dictionary_insert(alpha2_to_numeric, "SN", "686");
	dictionary_insert(alpha2_to_numeric, "RS", "688");
	dictionary_insert(alpha2_to_numeric, "SL", "694");
	dictionary_insert(alpha2_to_numeric, "SX", "534");
	dictionary_insert(alpha2_to_numeric, "SK", "703");
	dictionary_insert(alpha2_to_numeric, "SI", "705");
	dictionary_insert(alpha2_to_numeric, "SO", "706");
	dictionary_insert(alpha2_to_numeric, "ZA", "710");
	dictionary_insert(alpha2_to_numeric, "SS", "728");
	dictionary_insert(alpha2_to_numeric, "ES", "724");
	dictionary_insert(alpha2_to_numeric, "SD", "729");
	dictionary_insert(alpha2_to_numeric, "SR", "740");
	dictionary_insert(alpha2_to_numeric, "SE", "752");
	dictionary_insert(alpha2_to_numeric, "CH", "756");
	dictionary_insert(alpha2_to_numeric, "SY", "760");
	dictionary_insert(alpha2_to_numeric, "TW", "158");
	dictionary_insert(alpha2_to_numeric, "TJ", "762");
	dictionary_insert(alpha2_to_numeric, "TZ", "834");
	dictionary_insert(alpha2_to_numeric, "TH", "764");
	dictionary_insert(alpha2_to_numeric, "TL", "626");
	dictionary_insert(alpha2_to_numeric, "TG", "768");
	dictionary_insert(alpha2_to_numeric, "TN", "788");
	dictionary_insert(alpha2_to_numeric, "TR", "792");
	dictionary_insert(alpha2_to_numeric, "TM", "795");
	dictionary_insert(alpha2_to_numeric, "UG", "800");
	dictionary_insert(alpha2_to_numeric, "UA", "804");
	dictionary_insert(alpha2_to_numeric, "AE", "784");
	dictionary_insert(alpha2_to_numeric, "GB", "826");
	dictionary_insert(alpha2_to_numeric, "US", "840");
	dictionary_insert(alpha2_to_numeric, "UM", "581");
	dictionary_insert(alpha2_to_numeric, "UY", "858");
	dictionary_insert(alpha2_to_numeric, "UZ", "860");
	dictionary_insert(alpha2_to_numeric, "VE", "862");
	dictionary_insert(alpha2_to_numeric, "VN", "704");
	dictionary_insert(alpha2_to_numeric, "EH", "732");
	dictionary_insert(alpha2_to_numeric, "YE", "887");
	dictionary_insert(alpha2_to_numeric, "ZM", "894");
	dictionary_insert(alpha2_to_numeric, "ZW", "716");
}

void create_country_vertices()
{
	country_AF = construct_vertex(4, "AF");
	country_AL = construct_vertex(8, "AL");
	country_DZ = construct_vertex(12, "DZ");
	country_AD = construct_vertex(20, "AD");
	country_AO = construct_vertex(24, "AO");
	country_AR = construct_vertex(32, "AR");
	country_AM = construct_vertex(51, "AM");
	country_AT = construct_vertex(40, "AT");
	country_AZ = construct_vertex(31, "AZ");
	country_BD = construct_vertex(50, "BD");
	country_BY = construct_vertex(112, "BY");
	country_BE = construct_vertex(56, "BE");
	country_BZ = construct_vertex(84, "BZ");
	country_BJ = construct_vertex(204, "BJ");
	country_BT = construct_vertex(64, "BT");
	country_BO = construct_vertex(68, "BO");
	country_BA = construct_vertex(70, "BA");
	country_BW = construct_vertex(72, "BW");
	country_BR = construct_vertex(76, "BR");
	country_BN = construct_vertex(96, "BN");
	country_BG = construct_vertex(100, "BG");
	country_BF = construct_vertex(854, "BF");
	country_BI = construct_vertex(108, "BI");
	country_KH = construct_vertex(116, "KH");
	country_CM = construct_vertex(120, "CM");
	country_CA = construct_vertex(124, "CA");
	country_CF = construct_vertex(140, "CF");
	country_TD = construct_vertex(148, "TD");
	country_CL = construct_vertex(152, "CL");
	country_CN = construct_vertex(156, "CN");
	country_CO = construct_vertex(170, "CO");
	country_CG = construct_vertex(178, "CG");
	country_CD = construct_vertex(180, "CD");
	country_CR = construct_vertex(188, "CR");
	country_CI = construct_vertex(384, "CI");
	country_HR = construct_vertex(191, "HR");
	country_CZ = construct_vertex(203, "CZ");
	country_DK = construct_vertex(208, "DK");
	country_DJ = construct_vertex(262, "DJ");
	country_DO = construct_vertex(214, "DO");
	country_EC = construct_vertex(218, "EC");
	country_EG = construct_vertex(818, "EG");
	country_SV = construct_vertex(222, "SV");
	country_GQ = construct_vertex(226, "GQ");
	country_ER = construct_vertex(232, "ER");
	country_EE = construct_vertex(233, "EE");
	country_SZ = construct_vertex(748, "SZ");
	country_ET = construct_vertex(231, "ET");
	country_FI = construct_vertex(246, "FI");
	country_FR = construct_vertex(250, "FR");
	country_GF = construct_vertex(254, "GF");
	country_GA = construct_vertex(266, "GA");
	country_GM = construct_vertex(270, "GM");
	country_GE = construct_vertex(268, "GE");
	country_DE = construct_vertex(276, "DE");
	country_GH = construct_vertex(288, "GH");
	country_GI = construct_vertex(292, "GI");
	country_GR = construct_vertex(300, "GR");
	country_GT = construct_vertex(320, "GT");
	country_GN = construct_vertex(324, "GN");
	country_GW = construct_vertex(624, "GW");
	country_GY = construct_vertex(328, "GY");
	country_HT = construct_vertex(332, "HT");
	country_VA = construct_vertex(336, "VA");
	country_HN = construct_vertex(340, "HN");
	country_HK = construct_vertex(344, "HK");
	country_HU = construct_vertex(348, "HU");
	country_IN = construct_vertex(356, "IN");
	country_ID = construct_vertex(360, "ID");
	country_IR = construct_vertex(364, "IR");
	country_IQ = construct_vertex(368, "IQ");
	country_IE = construct_vertex(372, "IE");
	country_IL = construct_vertex(376, "IL");
	country_IT = construct_vertex(380, "IT");
	country_JO = construct_vertex(400, "JO");
	country_KZ = construct_vertex(398, "KZ");
	country_KE = construct_vertex(404, "KE");
	country_KP = construct_vertex(408, "KP");
	country_KR = construct_vertex(410, "KR");
	country_KW = construct_vertex(414, "KW");
	country_KG = construct_vertex(417, "KG");
	country_LA = construct_vertex(418, "LA");
	country_LV = construct_vertex(428, "LV");
	country_LB = construct_vertex(422, "LB");
	country_LS = construct_vertex(426, "LS");
	country_LR = construct_vertex(430, "LR");
	country_LY = construct_vertex(434, "LY");
	country_LI = construct_vertex(438, "LI");
	country_LT = construct_vertex(440, "LT");
	country_LU = construct_vertex(442, "LU");
	country_MO = construct_vertex(446, "MO");
	country_MW = construct_vertex(454, "MW");
	country_MY = construct_vertex(458, "MY");
	country_ML = construct_vertex(466, "ML");
	country_MR = construct_vertex(478, "MR");
	country_MX = construct_vertex(484, "MX");
	country_MD = construct_vertex(498, "MD");
	country_MC = construct_vertex(492, "MC");
	country_MN = construct_vertex(496, "MN");
	country_ME = construct_vertex(499, "ME");
	country_MA = construct_vertex(504, "MA");
	country_MZ = construct_vertex(508, "MZ");
	country_MM = construct_vertex(104, "MM");
	country_NA = construct_vertex(516, "NA");
	country_NP = construct_vertex(524, "NP");
	country_NL = construct_vertex(528, "NL");
	country_NI = construct_vertex(558, "NI");
	country_NE = construct_vertex(562, "NE");
	country_NG = construct_vertex(566, "NG");
	country_MK = construct_vertex(807, "MK");
	country_NO = construct_vertex(578, "NO");
	country_OM = construct_vertex(512, "OM");
	country_PK = construct_vertex(586, "PK");
	country_PS = construct_vertex(275, "PS");
	country_PA = construct_vertex(591, "PA");
	country_PG = construct_vertex(598, "PG");
	country_PY = construct_vertex(600, "PY");
	country_PE = construct_vertex(604, "PE");
	country_PL = construct_vertex(616, "PL");
	country_PT = construct_vertex(620, "PT");
	country_QA = construct_vertex(634, "QA");
	country_RO = construct_vertex(642, "RO");
	country_RU = construct_vertex(643, "RU");
	country_RW = construct_vertex(646, "RW");
	country_MF = construct_vertex(663, "MF");
	country_SM = construct_vertex(674, "SM");
	country_SA = construct_vertex(682, "SA");
	country_SN = construct_vertex(686, "SN");
	country_RS = construct_vertex(688, "RS");
	country_SL = construct_vertex(694, "SL");
	country_SX = construct_vertex(534, "SX");
	country_SK = construct_vertex(703, "SK");
	country_SI = construct_vertex(705, "SI");
	country_SO = construct_vertex(706, "SO");
	country_ZA = construct_vertex(710, "ZA");
	country_SS = construct_vertex(728, "SS");
	country_ES = construct_vertex(724, "ES");
	country_SD = construct_vertex(729, "SD");
	country_SR = construct_vertex(740, "SR");
	country_SE = construct_vertex(752, "SE");
	country_CH = construct_vertex(756, "CH");
	country_SY = construct_vertex(760, "SY");
	country_TW = construct_vertex(158, "TW");
	country_TJ = construct_vertex(762, "TJ");
	country_TZ = construct_vertex(834, "TZ");
	country_TH = construct_vertex(764, "TH");
	country_TL = construct_vertex(626, "TL");
	country_TG = construct_vertex(768, "TG");
	country_TN = construct_vertex(788, "TN");
	country_TR = construct_vertex(792, "TR");
	country_TM = construct_vertex(795, "TM");
	country_UG = construct_vertex(800, "UG");
	country_UA = construct_vertex(804, "UA");
	country_AE = construct_vertex(784, "AE");
	country_GB = construct_vertex(826, "GB");
	country_US = construct_vertex(840, "US");
	country_UM = construct_vertex(581, "UM");
	country_UY = construct_vertex(858, "UY");
	country_UZ = construct_vertex(860, "UZ");
	country_VE = construct_vertex(862, "VE");
	country_VN = construct_vertex(704, "VN");
	country_EH = construct_vertex(732, "EH");
	country_YE = construct_vertex(887, "YE");
	country_ZM = construct_vertex(894, "ZM");
	country_ZW = construct_vertex(716, "ZW");
}

void populate_vertex_array(struct Vertex * countryVertices[])
{
	countryVertices[4] = country_AF;
	countryVertices[8] = country_AL;
	countryVertices[12] = country_DZ;
	countryVertices[20] = country_AD;
	countryVertices[24] = country_AO;
	countryVertices[32] = country_AR;
	countryVertices[51] = country_AM;
	countryVertices[40] = country_AT;
	countryVertices[31] = country_AZ;
	countryVertices[50] = country_BD;
	countryVertices[112] = country_BY;
	countryVertices[56] = country_BE;
	countryVertices[84] = country_BZ;
	countryVertices[204] = country_BJ;
	countryVertices[64] = country_BT;
	countryVertices[68] = country_BO;
	countryVertices[70] = country_BA;
	countryVertices[72] = country_BW;
	countryVertices[76] = country_BR;
	countryVertices[96] = country_BN;
	countryVertices[100] = country_BG;
	countryVertices[854] = country_BF;
	countryVertices[108] = country_BI;
	countryVertices[116] = country_KH;
	countryVertices[120] = country_CM;
	countryVertices[124] = country_CA;
	countryVertices[140] = country_CF;
	countryVertices[148] = country_TD;
	countryVertices[152] = country_CL;
	countryVertices[156] = country_CN;
	countryVertices[170] = country_CO;
	countryVertices[178] = country_CG;
	countryVertices[180] = country_CD;
	countryVertices[188] = country_CR;
	countryVertices[384] = country_CI;
	countryVertices[191] = country_HR;
	countryVertices[203] = country_CZ;
	countryVertices[208] = country_DK;
	countryVertices[262] = country_DJ;
	countryVertices[214] = country_DO;
	countryVertices[218] = country_EC;
	countryVertices[818] = country_EG;
	countryVertices[222] = country_SV;
	countryVertices[226] = country_GQ;
	countryVertices[232] = country_ER;
	countryVertices[233] = country_EE;
	countryVertices[748] = country_SZ;
	countryVertices[231] = country_ET;
	countryVertices[246] = country_FI;
	countryVertices[250] = country_FR;
	countryVertices[254] = country_GF;
	countryVertices[266] = country_GA;
	countryVertices[270] = country_GM;
	countryVertices[268] = country_GE;
	countryVertices[276] = country_DE;
	countryVertices[288] = country_GH;
	countryVertices[292] = country_GI;
	countryVertices[300] = country_GR;
	countryVertices[320] = country_GT;
	countryVertices[324] = country_GN;
	countryVertices[624] = country_GW;
	countryVertices[328] = country_GY;
	countryVertices[332] = country_HT;
	countryVertices[336] = country_VA;
	countryVertices[340] = country_HN;
	countryVertices[344] = country_HK;
	countryVertices[348] = country_HU;
	countryVertices[356] = country_IN;
	countryVertices[360] = country_ID;
	countryVertices[364] = country_IR;
	countryVertices[368] = country_IQ;
	countryVertices[372] = country_IE;
	countryVertices[376] = country_IL;
	countryVertices[380] = country_IT;
	countryVertices[400] = country_JO;
	countryVertices[398] = country_KZ;
	countryVertices[404] = country_KE;
	countryVertices[408] = country_KP;
	countryVertices[410] = country_KR;
	countryVertices[414] = country_KW;
	countryVertices[417] = country_KG;
	countryVertices[418] = country_LA;
	countryVertices[428] = country_LV;
	countryVertices[422] = country_LB;
	countryVertices[426] = country_LS;
	countryVertices[430] = country_LR;
	countryVertices[434] = country_LY;
	countryVertices[438] = country_LI;
	countryVertices[440] = country_LT;
	countryVertices[442] = country_LU;
	countryVertices[446] = country_MO;
	countryVertices[454] = country_MW;
	countryVertices[458] = country_MY;
	countryVertices[466] = country_ML;
	countryVertices[478] = country_MR;
	countryVertices[484] = country_MX;
	countryVertices[498] = country_MD;
	countryVertices[492] = country_MC;
	countryVertices[496] = country_MN;
	countryVertices[499] = country_ME;
	countryVertices[504] = country_MA;
	countryVertices[508] = country_MZ;
	countryVertices[104] = country_MM;
	countryVertices[516] = country_NA;
	countryVertices[524] = country_NP;
	countryVertices[528] = country_NL;
	countryVertices[558] = country_NI;
	countryVertices[562] = country_NE;
	countryVertices[566] = country_NG;
	countryVertices[807] = country_MK;
	countryVertices[578] = country_NO;
	countryVertices[512] = country_OM;
	countryVertices[586] = country_PK;
	countryVertices[275] = country_PS;
	countryVertices[591] = country_PA;
	countryVertices[598] = country_PG;
	countryVertices[600] = country_PY;
	countryVertices[604] = country_PE;
	countryVertices[616] = country_PL;
	countryVertices[620] = country_PT;
	countryVertices[634] = country_QA;
	countryVertices[642] = country_RO;
	countryVertices[643] = country_RU;
	countryVertices[646] = country_RW;
	countryVertices[663] = country_MF;
	countryVertices[674] = country_SM;
	countryVertices[682] = country_SA;
	countryVertices[686] = country_SN;
	countryVertices[688] = country_RS;
	countryVertices[694] = country_SL;
	countryVertices[534] = country_SX;
	countryVertices[703] = country_SK;
	countryVertices[705] = country_SI;
	countryVertices[706] = country_SO;
	countryVertices[710] = country_ZA;
	countryVertices[728] = country_SS;
	countryVertices[724] = country_ES;
	countryVertices[729] = country_SD;
	countryVertices[740] = country_SR;
	countryVertices[752] = country_SE;
	countryVertices[756] = country_CH;
	countryVertices[760] = country_SY;
	countryVertices[158] = country_TW;
	countryVertices[762] = country_TJ;
	countryVertices[834] = country_TZ;
	countryVertices[764] = country_TH;
	countryVertices[626] = country_TL;
	countryVertices[768] = country_TG;
	countryVertices[788] = country_TN;
	countryVertices[792] = country_TR;
	countryVertices[795] = country_TM;
	countryVertices[800] = country_UG;
	countryVertices[804] = country_UA;
	countryVertices[784] = country_AE;
	countryVertices[826] = country_GB;
	countryVertices[840] = country_US;
	countryVertices[581] = country_UM;
	countryVertices[858] = country_UY;
	countryVertices[860] = country_UZ;
	countryVertices[862] = country_VE;
	countryVertices[704] = country_VN;
	countryVertices[732] = country_EH;
	countryVertices[887] = country_YE;
	countryVertices[894] = country_ZM;
	countryVertices[716] = country_ZW;
}

void create_country_edges()
{
	add_edge(country_AD, country_FR);
	add_edge(country_AD, country_ES);
	add_edge(country_AE, country_OM);
	add_edge(country_AE, country_SA);
	add_edge(country_AF, country_CN);
	add_edge(country_AF, country_IR);
	add_edge(country_AF, country_PK);
	add_edge(country_AF, country_TJ);
	add_edge(country_AF, country_TM);
	add_edge(country_AF, country_UZ);
	add_edge(country_AL, country_GR);
	add_edge(country_AL, country_ME);
	add_edge(country_AL, country_MK);
	add_edge(country_AL, country_RS);
	add_edge(country_AM, country_AZ);
	add_edge(country_AM, country_GE);
	add_edge(country_AM, country_IR);
	add_edge(country_AM, country_TR);
	add_edge(country_AO, country_CG);
	add_edge(country_AO, country_CD);
	add_edge(country_AO, country_NA);
	add_edge(country_AO, country_ZM);
	add_edge(country_AR, country_BO);
	add_edge(country_AR, country_BR);
	add_edge(country_AR, country_CL);
	add_edge(country_AR, country_PY);
	add_edge(country_AR, country_UY);
	add_edge(country_AT, country_CZ);
	add_edge(country_AT, country_DE);
	add_edge(country_AT, country_HU);
	add_edge(country_AT, country_IT);
	add_edge(country_AT, country_LI);
	add_edge(country_AT, country_SK);
	add_edge(country_AT, country_SI);
	add_edge(country_AT, country_CH);
	add_edge(country_AZ, country_AM);
	add_edge(country_AZ, country_GE);
	add_edge(country_AZ, country_IR);
	add_edge(country_AZ, country_RU);
	add_edge(country_AZ, country_TR);
	add_edge(country_BA, country_HR);
	add_edge(country_BA, country_ME);
	add_edge(country_BA, country_RS);
	add_edge(country_BD, country_IN);
	add_edge(country_BD, country_MM);
	add_edge(country_BE, country_FR);
	add_edge(country_BE, country_DE);
	add_edge(country_BE, country_LU);
	add_edge(country_BE, country_NL);
	add_edge(country_BF, country_BJ);
	add_edge(country_BF, country_CI);
	add_edge(country_BF, country_GH);
	add_edge(country_BF, country_ML);
	add_edge(country_BF, country_NE);
	add_edge(country_BF, country_TG);
	add_edge(country_BG, country_GR);
	add_edge(country_BG, country_MK);
	add_edge(country_BG, country_RO);
	add_edge(country_BG, country_RS);
	add_edge(country_BG, country_TR);
	add_edge(country_BI, country_CD);
	add_edge(country_BI, country_RW);
	add_edge(country_BI, country_TZ);
	add_edge(country_BJ, country_BF);
	add_edge(country_BJ, country_NE);
	add_edge(country_BJ, country_NG);
	add_edge(country_BJ, country_TG);
	add_edge(country_BN, country_MY);
	add_edge(country_BO, country_AR);
	add_edge(country_BO, country_BR);
	add_edge(country_BO, country_CL);
	add_edge(country_BO, country_PY);
	add_edge(country_BO, country_PE);
	add_edge(country_BR, country_AR);
	add_edge(country_BR, country_BO);
	add_edge(country_BR, country_CO);
	add_edge(country_BR, country_GF);
	add_edge(country_BR, country_GY);
	add_edge(country_BR, country_PY);
	add_edge(country_BR, country_PE);
	add_edge(country_BR, country_SR);
	add_edge(country_BR, country_UY);
	add_edge(country_BR, country_VE);
	add_edge(country_BT, country_CN);
	add_edge(country_BT, country_IN);
	add_edge(country_BW, country_NA);
	add_edge(country_BW, country_ZA);
	add_edge(country_BW, country_ZM);
	add_edge(country_BW, country_ZW);
	add_edge(country_BY, country_LV);
	add_edge(country_BY, country_LT);
	add_edge(country_BY, country_PL);
	add_edge(country_BY, country_RU);
	add_edge(country_BY, country_UA);
	add_edge(country_BZ, country_GT);
	add_edge(country_BZ, country_MX);
	add_edge(country_CA, country_US);
	add_edge(country_CD, country_AO);
	add_edge(country_CD, country_BI);
	add_edge(country_CD, country_CF);
	add_edge(country_CD, country_CG);
	add_edge(country_CD, country_RW);
	add_edge(country_CD, country_SS);
	add_edge(country_CD, country_TZ);
	add_edge(country_CD, country_UG);
	add_edge(country_CD, country_ZM);
	add_edge(country_CF, country_CM);
	add_edge(country_CF, country_TD);
	add_edge(country_CF, country_CG);
	add_edge(country_CF, country_CD);
	add_edge(country_CF, country_SS);
	add_edge(country_CF, country_SD);
	add_edge(country_CG, country_AO);
	add_edge(country_CG, country_CM);
	add_edge(country_CG, country_CF);
	add_edge(country_CG, country_CD);
	add_edge(country_CG, country_GA);
	add_edge(country_CH, country_AT);
	add_edge(country_CH, country_FR);
	add_edge(country_CH, country_DE);
	add_edge(country_CH, country_IT);
	add_edge(country_CH, country_LI);
	add_edge(country_CI, country_BF);
	add_edge(country_CI, country_GH);
	add_edge(country_CI, country_GN);
	add_edge(country_CI, country_LR);
	add_edge(country_CI, country_ML);
	add_edge(country_CL, country_AR);
	add_edge(country_CL, country_BO);
	add_edge(country_CL, country_PE);
	add_edge(country_CM, country_CF);
	add_edge(country_CM, country_TD);
	add_edge(country_CM, country_CG);
	add_edge(country_CM, country_GQ);
	add_edge(country_CM, country_GA);
	add_edge(country_CM, country_NG);
	add_edge(country_CN, country_AF);
	add_edge(country_CN, country_BT);
	add_edge(country_CN, country_HK);
	add_edge(country_CN, country_IN);
	add_edge(country_CN, country_KZ);
	add_edge(country_CN, country_KP);
	add_edge(country_CN, country_KG);
	add_edge(country_CN, country_LA);
	add_edge(country_CN, country_MO);
	add_edge(country_CN, country_MN);
	add_edge(country_CN, country_MM);
	add_edge(country_CN, country_NP);
	add_edge(country_CN, country_PK);
	add_edge(country_CN, country_RU);
	add_edge(country_CN, country_TJ);
	add_edge(country_CN, country_VN);
	add_edge(country_CO, country_BR);
	add_edge(country_CO, country_EC);
	add_edge(country_CO, country_PA);
	add_edge(country_CO, country_PE);
	add_edge(country_CO, country_VE);
	add_edge(country_CR, country_NI);
	add_edge(country_CR, country_PA);
	add_edge(country_CZ, country_AT);
	add_edge(country_CZ, country_DE);
	add_edge(country_CZ, country_PL);
	add_edge(country_CZ, country_SK);
	add_edge(country_DE, country_AT);
	add_edge(country_DE, country_BE);
	add_edge(country_DE, country_CZ);
	add_edge(country_DE, country_DK);
	add_edge(country_DE, country_FR);
	add_edge(country_DE, country_LU);
	add_edge(country_DE, country_NL);
	add_edge(country_DE, country_PL);
	add_edge(country_DE, country_CH);
	add_edge(country_DJ, country_ER);
	add_edge(country_DJ, country_ET);
	add_edge(country_DJ, country_SO);
	add_edge(country_DK, country_DE);
	add_edge(country_DO, country_HT);
	add_edge(country_DZ, country_LY);
	add_edge(country_DZ, country_ML);
	add_edge(country_DZ, country_MR);
	add_edge(country_DZ, country_MA);
	add_edge(country_DZ, country_NE);
	add_edge(country_DZ, country_TN);
	add_edge(country_DZ, country_EH);
	add_edge(country_EC, country_CO);
	add_edge(country_EC, country_PE);
	add_edge(country_EE, country_LV);
	add_edge(country_EE, country_RU);
	add_edge(country_EG, country_IL);
	add_edge(country_EG, country_LY);
	add_edge(country_EG, country_PS);
	add_edge(country_EG, country_SD);
	add_edge(country_EH, country_DZ);
	add_edge(country_EH, country_MR);
	add_edge(country_EH, country_MA);
	add_edge(country_ER, country_DJ);
	add_edge(country_ER, country_ET);
	add_edge(country_ER, country_SD);
	add_edge(country_ES, country_AD);
	add_edge(country_ES, country_FR);
	add_edge(country_ES, country_GI);
	add_edge(country_ES, country_MA);
	add_edge(country_ES, country_PT);
	add_edge(country_ET, country_DJ);
	add_edge(country_ET, country_ER);
	add_edge(country_ET, country_KE);
	add_edge(country_ET, country_SO);
	add_edge(country_ET, country_SS);
	add_edge(country_ET, country_SD);
	add_edge(country_FI, country_NO);
	add_edge(country_FI, country_RU);
	add_edge(country_FI, country_SE);
	add_edge(country_FR, country_AD);
	add_edge(country_FR, country_BE);
	add_edge(country_FR, country_DE);
	add_edge(country_FR, country_IT);
	add_edge(country_FR, country_LU);
	add_edge(country_FR, country_MC);
	add_edge(country_FR, country_ES);
	add_edge(country_FR, country_CH);
	add_edge(country_GA, country_CM);
	add_edge(country_GA, country_CG);
	add_edge(country_GA, country_GQ);
	add_edge(country_GB, country_IE);
	add_edge(country_GE, country_AM);
	add_edge(country_GE, country_AZ);
	add_edge(country_GE, country_RU);
	add_edge(country_GE, country_TR);
	add_edge(country_GF, country_BR);
	add_edge(country_GF, country_SR);
	add_edge(country_GH, country_BF);
	add_edge(country_GH, country_CI);
	add_edge(country_GH, country_TG);
	add_edge(country_GI, country_ES);
	add_edge(country_GM, country_SN);
	add_edge(country_GN, country_CI);
	add_edge(country_GN, country_GW);
	add_edge(country_GN, country_LR);
	add_edge(country_GN, country_ML);
	add_edge(country_GN, country_SN);
	add_edge(country_GN, country_SL);
	add_edge(country_GQ, country_CM);
	add_edge(country_GQ, country_GA);
	add_edge(country_GR, country_AL);
	add_edge(country_GR, country_BG);
	add_edge(country_GR, country_MK);
	add_edge(country_GR, country_TR);
	add_edge(country_GT, country_BZ);
	add_edge(country_GT, country_SV);
	add_edge(country_GT, country_HN);
	add_edge(country_GT, country_MX);
	add_edge(country_GW, country_GN);
	add_edge(country_GW, country_SN);
	add_edge(country_GY, country_BR);
	add_edge(country_GY, country_SR);
	add_edge(country_GY, country_VE);
	add_edge(country_HK, country_CN);
	add_edge(country_HN, country_SV);
	add_edge(country_HN, country_GT);
	add_edge(country_HN, country_NI);
	add_edge(country_HR, country_BA);
	add_edge(country_HR, country_HU);
	add_edge(country_HR, country_ME);
	add_edge(country_HR, country_RS);
	add_edge(country_HR, country_SI);
	add_edge(country_HT, country_DO);
	add_edge(country_HU, country_AT);
	add_edge(country_HU, country_HR);
	add_edge(country_HU, country_RO);
	add_edge(country_HU, country_RS);
	add_edge(country_HU, country_SK);
	add_edge(country_HU, country_SI);
	add_edge(country_HU, country_UA);
	add_edge(country_ID, country_MY);
	add_edge(country_ID, country_PG);
	add_edge(country_ID, country_TL);
	add_edge(country_IE, country_GB);
	add_edge(country_IL, country_EG);
	add_edge(country_IL, country_JO);
	add_edge(country_IL, country_LB);
	add_edge(country_IL, country_PS);
	add_edge(country_IL, country_SY);
	add_edge(country_IN, country_BD);
	add_edge(country_IN, country_BT);
	add_edge(country_IN, country_CN);
	add_edge(country_IN, country_MM);
	add_edge(country_IN, country_NP);
	add_edge(country_IN, country_PK);
	add_edge(country_IQ, country_IR);
	add_edge(country_IQ, country_JO);
	add_edge(country_IQ, country_KW);
	add_edge(country_IQ, country_SA);
	add_edge(country_IQ, country_SY);
	add_edge(country_IQ, country_TR);
	add_edge(country_IR, country_AF);
	add_edge(country_IR, country_AM);
	add_edge(country_IR, country_AZ);
	add_edge(country_IR, country_IQ);
	add_edge(country_IR, country_PK);
	add_edge(country_IR, country_TR);
	add_edge(country_IR, country_TM);
	add_edge(country_IT, country_AT);
	add_edge(country_IT, country_FR);
	add_edge(country_IT, country_SM);
	add_edge(country_IT, country_SI);
	add_edge(country_IT, country_CH);
	add_edge(country_IT, country_VA);
	add_edge(country_JO, country_IQ);
	add_edge(country_JO, country_IL);
	add_edge(country_JO, country_PS);
	add_edge(country_JO, country_SA);
	add_edge(country_JO, country_SY);
	add_edge(country_KE, country_ET);
	add_edge(country_KE, country_SO);
	add_edge(country_KE, country_SS);
	add_edge(country_KE, country_TZ);
	add_edge(country_KE, country_UG);
	add_edge(country_KG, country_CN);
	add_edge(country_KG, country_KZ);
	add_edge(country_KG, country_TJ);
	add_edge(country_KG, country_UZ);
	add_edge(country_KH, country_LA);
	add_edge(country_KH, country_TH);
	add_edge(country_KH, country_VN);
	add_edge(country_KP, country_CN);
	add_edge(country_KP, country_KR);
	add_edge(country_KP, country_RU);
	add_edge(country_KR, country_KP);
	add_edge(country_KW, country_IQ);
	add_edge(country_KW, country_SA);
	add_edge(country_KZ, country_CN);
	add_edge(country_KZ, country_KG);
	add_edge(country_KZ, country_RU);
	add_edge(country_KZ, country_TM);
	add_edge(country_KZ, country_UZ);
	add_edge(country_LA, country_CN);
	add_edge(country_LA, country_KH);
	add_edge(country_LA, country_MM);
	add_edge(country_LA, country_TH);
	add_edge(country_LA, country_VN);
	add_edge(country_LB, country_IL);
	add_edge(country_LB, country_SY);
	add_edge(country_LI, country_AT);
	add_edge(country_LI, country_CH);
	add_edge(country_LR, country_CI);
	add_edge(country_LR, country_GN);
	add_edge(country_LR, country_SL);
	add_edge(country_LS, country_ZA);
	add_edge(country_LT, country_BY);
	add_edge(country_LT, country_LV);
	add_edge(country_LT, country_PL);
	add_edge(country_LT, country_RU);
	add_edge(country_LU, country_BE);
	add_edge(country_LU, country_DE);
	add_edge(country_LU, country_FR);
	add_edge(country_LV, country_BY);
	add_edge(country_LV, country_EE);
	add_edge(country_LV, country_LT);
	add_edge(country_LV, country_RU);
	add_edge(country_LY, country_DZ);
	add_edge(country_LY, country_TD);
	add_edge(country_LY, country_EG);
	add_edge(country_LY, country_NE);
	add_edge(country_LY, country_SD);
	add_edge(country_LY, country_TN);
	add_edge(country_MA, country_DZ);
	add_edge(country_MA, country_ES);
	add_edge(country_MA, country_EH);
	add_edge(country_MC, country_FR);
	add_edge(country_MD, country_RO);
	add_edge(country_MD, country_UA);
	add_edge(country_ME, country_AL);
	add_edge(country_ME, country_BA);
	add_edge(country_ME, country_HR);
	add_edge(country_ME, country_RS);
	add_edge(country_MF, country_SX);
	add_edge(country_MK, country_AL);
	add_edge(country_MK, country_BG);
	add_edge(country_MK, country_GR);
	add_edge(country_MK, country_RS);
	add_edge(country_ML, country_DZ);
	add_edge(country_ML, country_BF);
	add_edge(country_ML, country_CI);
	add_edge(country_ML, country_GN);
	add_edge(country_ML, country_MR);
	add_edge(country_ML, country_NE);
	add_edge(country_ML, country_SN);
	add_edge(country_MM, country_BD);
	add_edge(country_MM, country_CN);
	add_edge(country_MM, country_IN);
	add_edge(country_MM, country_LA);
	add_edge(country_MM, country_TH);
	add_edge(country_MN, country_CN);
	add_edge(country_MN, country_RU);
	add_edge(country_MO, country_CN);
	add_edge(country_MR, country_DZ);
	add_edge(country_MR, country_ML);
	add_edge(country_MR, country_SN);
	add_edge(country_MR, country_EH);
	add_edge(country_MW, country_MZ);
	add_edge(country_MW, country_TZ);
	add_edge(country_MW, country_ZM);
	add_edge(country_MX, country_BZ);
	add_edge(country_MX, country_GT);
	add_edge(country_MX, country_US);
	add_edge(country_MY, country_BN);
	add_edge(country_MY, country_ID);
	add_edge(country_MY, country_TH);
	add_edge(country_MZ, country_MW);
	add_edge(country_MZ, country_SZ);
	add_edge(country_MZ, country_ZA);
	add_edge(country_MZ, country_TZ);
	add_edge(country_MZ, country_ZM);
	add_edge(country_MZ, country_ZW);
	add_edge(country_NA, country_AO);
	add_edge(country_NA, country_BW);
	add_edge(country_NA, country_ZA);
	add_edge(country_NA, country_ZM);
	add_edge(country_NE, country_DZ);
	add_edge(country_NE, country_BJ);
	add_edge(country_NE, country_BF);
	add_edge(country_NE, country_TD);
	add_edge(country_NE, country_LY);
	add_edge(country_NE, country_ML);
	add_edge(country_NE, country_NG);
	add_edge(country_NG, country_BJ);
	add_edge(country_NG, country_CM);
	add_edge(country_NG, country_TD);
	add_edge(country_NG, country_NE);
	add_edge(country_NI, country_CR);
	add_edge(country_NI, country_HN);
	add_edge(country_NL, country_BE);
	add_edge(country_NL, country_DE);
	add_edge(country_NO, country_FI);
	add_edge(country_NO, country_RU);
	add_edge(country_NO, country_SE);
	add_edge(country_NP, country_CN);
	add_edge(country_NP, country_IN);
	add_edge(country_OM, country_AE);
	add_edge(country_OM, country_SA);
	add_edge(country_OM, country_YE);
	add_edge(country_PA, country_CO);
	add_edge(country_PA, country_CR);
	add_edge(country_PE, country_BO);
	add_edge(country_PE, country_BR);
	add_edge(country_PE, country_CL);
	add_edge(country_PE, country_CO);
	add_edge(country_PE, country_EC);
	add_edge(country_PG, country_ID);
	add_edge(country_PK, country_AF);
	add_edge(country_PK, country_CN);
	add_edge(country_PK, country_IN);
	add_edge(country_PK, country_IR);
	add_edge(country_PL, country_BY);
	add_edge(country_PL, country_CZ);
	add_edge(country_PL, country_DE);
	add_edge(country_PL, country_LT);
	add_edge(country_PL, country_RU);
	add_edge(country_PL, country_SK);
	add_edge(country_PL, country_UA);
	add_edge(country_PS, country_EG);
	add_edge(country_PS, country_IL);
	add_edge(country_PS, country_JO);
	add_edge(country_PT, country_ES);
	add_edge(country_PY, country_AR);
	add_edge(country_PY, country_BO);
	add_edge(country_PY, country_BR);
	add_edge(country_QA, country_SA);
	add_edge(country_RO, country_BG);
	add_edge(country_RO, country_HU);
	add_edge(country_RO, country_MD);
	add_edge(country_RO, country_RS);
	add_edge(country_RO, country_UA);
	add_edge(country_RS, country_AL);
	add_edge(country_RS, country_BA);
	add_edge(country_RS, country_BG);
	add_edge(country_RS, country_HR);
	add_edge(country_RS, country_HU);
	add_edge(country_RS, country_ME);
	add_edge(country_RS, country_MK);
	add_edge(country_RS, country_RO);
	add_edge(country_RU, country_AZ);
	add_edge(country_RU, country_BY);
	add_edge(country_RU, country_CN);
	add_edge(country_RU, country_EE);
	add_edge(country_RU, country_FI);
	add_edge(country_RU, country_GE);
	add_edge(country_RU, country_KZ);
	add_edge(country_RU, country_KP);
	add_edge(country_RU, country_LV);
	add_edge(country_RU, country_LT);
	add_edge(country_RU, country_MN);
	add_edge(country_RU, country_NO);
	add_edge(country_RU, country_PL);
	add_edge(country_RU, country_UA);
	add_edge(country_RW, country_BI);
	add_edge(country_RW, country_CD);
	add_edge(country_RW, country_TZ);
	add_edge(country_RW, country_UG);
	add_edge(country_SA, country_IQ);
	add_edge(country_SA, country_JO);
	add_edge(country_SA, country_KW);
	add_edge(country_SA, country_OM);
	add_edge(country_SA, country_QA);
	add_edge(country_SA, country_AE);
	add_edge(country_SA, country_YE);
	add_edge(country_SD, country_CF);
	add_edge(country_SD, country_TD);
	add_edge(country_SD, country_EG);
	add_edge(country_SD, country_ET);
	add_edge(country_SD, country_ER);
	add_edge(country_SD, country_LY);
	add_edge(country_SD, country_SS);
	add_edge(country_SE, country_FI);
	add_edge(country_SE, country_NO);
	add_edge(country_SI, country_AT);
	add_edge(country_SI, country_HR);
	add_edge(country_SI, country_HU);
	add_edge(country_SI, country_IT);
	add_edge(country_SK, country_AT);
	add_edge(country_SK, country_CZ);
	add_edge(country_SK, country_HU);
	add_edge(country_SK, country_PL);
	add_edge(country_SK, country_UA);
	add_edge(country_SL, country_GN);
	add_edge(country_SL, country_LR);
	add_edge(country_SM, country_IT);
	add_edge(country_SN, country_GM);
	add_edge(country_SN, country_GN);
	add_edge(country_SN, country_GW);
	add_edge(country_SN, country_ML);
	add_edge(country_SN, country_MR);
	add_edge(country_SO, country_DJ);
	add_edge(country_SO, country_ET);
	add_edge(country_SO, country_KE);
	add_edge(country_SR, country_BR);
	add_edge(country_SR, country_GF);
	add_edge(country_SR, country_GY);
	add_edge(country_SS, country_CF);
	add_edge(country_SS, country_CD);
	add_edge(country_SS, country_ET);
	add_edge(country_SS, country_KE);
	add_edge(country_SS, country_SD);
	add_edge(country_SS, country_UG);
	add_edge(country_SV, country_GT);
	add_edge(country_SV, country_HN);
	add_edge(country_SX, country_MF);
	add_edge(country_SY, country_IQ);
	add_edge(country_SY, country_IL);
	add_edge(country_SY, country_JO);
	add_edge(country_SY, country_LB);
	add_edge(country_SY, country_TR);
	add_edge(country_SZ, country_MZ);
	add_edge(country_SZ, country_ZA);
	add_edge(country_TD, country_CM);
	add_edge(country_TD, country_CF);
	add_edge(country_TD, country_LY);
	add_edge(country_TD, country_NE);
	add_edge(country_TD, country_NG);
	add_edge(country_TD, country_SD);
	add_edge(country_TG, country_BJ);
	add_edge(country_TG, country_BF);
	add_edge(country_TG, country_GH);
	add_edge(country_TH, country_KH);
	add_edge(country_TH, country_LA);
	add_edge(country_TH, country_MY);
	add_edge(country_TH, country_MM);
	add_edge(country_TJ, country_AF);
	add_edge(country_TJ, country_CN);
	add_edge(country_TJ, country_KG);
	add_edge(country_TJ, country_UZ);
	add_edge(country_TL, country_ID);
	add_edge(country_TM, country_AF);
	add_edge(country_TM, country_IR);
	add_edge(country_TM, country_KZ);
	add_edge(country_TM, country_UZ);
	add_edge(country_TN, country_DZ);
	add_edge(country_TN, country_LY);
	add_edge(country_TR, country_AM);
	add_edge(country_TR, country_AZ);
	add_edge(country_TR, country_BG);
	add_edge(country_TR, country_GE);
	add_edge(country_TR, country_GR);
	add_edge(country_TR, country_IR);
	add_edge(country_TR, country_IQ);
	add_edge(country_TR, country_SY);
	add_edge(country_TZ, country_BI);
	add_edge(country_TZ, country_CD);
	add_edge(country_TZ, country_KE);
	add_edge(country_TZ, country_MW);
	add_edge(country_TZ, country_MZ);
	add_edge(country_TZ, country_RW);
	add_edge(country_TZ, country_UG);
	add_edge(country_TZ, country_ZM);
	add_edge(country_UA, country_BY);
	add_edge(country_UA, country_HU);
	add_edge(country_UA, country_MD);
	add_edge(country_UA, country_PL);
	add_edge(country_UA, country_RO);
	add_edge(country_UA, country_RU);
	add_edge(country_UA, country_SK);
	add_edge(country_UG, country_CD);
	add_edge(country_UG, country_KE);
	add_edge(country_UG, country_RW);
	add_edge(country_UG, country_SS);
	add_edge(country_UG, country_TZ);
	add_edge(country_US, country_CA);
	add_edge(country_US, country_MX);
	add_edge(country_UY, country_AR);
	add_edge(country_UY, country_BR);
	add_edge(country_UZ, country_AF);
	add_edge(country_UZ, country_KZ);
	add_edge(country_UZ, country_KG);
	add_edge(country_UZ, country_TJ);
	add_edge(country_UZ, country_TM);
	add_edge(country_VA, country_IT);
	add_edge(country_VE, country_BR);
	add_edge(country_VE, country_CO);
	add_edge(country_VE, country_GY);
	add_edge(country_VN, country_KH);
	add_edge(country_VN, country_CN);
	add_edge(country_VN, country_LA);
	add_edge(country_YE, country_OM);
	add_edge(country_YE, country_SA);
	add_edge(country_ZA, country_BW);
	add_edge(country_ZA, country_LS);
	add_edge(country_ZA, country_MZ);
	add_edge(country_ZA, country_NA);
	add_edge(country_ZA, country_SZ);
	add_edge(country_ZA, country_ZW);
	add_edge(country_ZM, country_AO);
	add_edge(country_ZM, country_BW);
	add_edge(country_ZM, country_CD);
	add_edge(country_ZM, country_MW);
	add_edge(country_ZM, country_MZ);
	add_edge(country_ZM, country_NA);
	add_edge(country_ZM, country_TZ);
	add_edge(country_ZM, country_ZW);
	add_edge(country_ZW, country_BW);
	add_edge(country_ZW, country_MZ);
	add_edge(country_ZW, country_ZA);
	add_edge(country_ZW, country_ZM);
}

void free_strings()
{
	free(AF_name);
	free(AL_name);
	free(DZ_name);
	free(AD_name);
	free(AO_name);
	free(AR_name);
	free(AM_name);
	free(AT_name);
	free(AZ_name);
	free(BD_name);
	free(BY_name);
	free(BE_name);
	free(BZ_name);
	free(BJ_name);
	free(BT_name);
	free(BO_name);
	free(BA_name);
	free(BW_name);
	free(BR_name);
	free(BN_name);
	free(BG_name);
	free(BF_name);
	free(BI_name);
	free(KH_name);
	free(CM_name);
	free(CA_name);
	free(CF_name);
	free(TD_name);
	free(CL_name);
	free(CN_name);
	free(CO_name);
	free(CG_name);
	free(CD_name);
	free(CR_name);
	free(CI_name);
	free(HR_name);
	free(CZ_name);
	free(DK_name);
	free(DJ_name);
	free(DO_name);
	free(EC_name);
	free(EG_name);
	free(SV_name);
	free(GQ_name);
	free(ER_name);
	free(EE_name);
	free(SZ_name);
	free(ET_name);
	free(FI_name);
	free(FR_name);
	free(GF_name);
	free(GA_name);
	free(GM_name);
	free(GE_name);
	free(DE_name);
	free(GH_name);
	free(GI_name);
	free(GR_name);
	free(GT_name);
	free(GN_name);
	free(GW_name);
	free(GY_name);
	free(HT_name);
	free(VA_name);
	free(HN_name);
	free(HK_name);
	free(HU_name);
	free(IN_name);
	free(ID_name);
	free(IR_name);
	free(IQ_name);
	free(IE_name);
	free(IL_name);
	free(IT_name);
	free(JO_name);
	free(KZ_name);
	free(KE_name);
	free(KP_name);
	free(KR_name);
	free(KW_name);
	free(KG_name);
	free(LA_name);
	free(LV_name);
	free(LB_name);
	free(LS_name);
	free(LR_name);
	free(LY_name);
	free(LI_name);
	free(LT_name);
	free(LU_name);
	free(MO_name);
	free(MW_name);
	free(MY_name);
	free(ML_name);
	free(MR_name);
	free(MX_name);
	free(MD_name);
	free(MC_name);
	free(MN_name);
	free(ME_name);
	free(MA_name);
	free(MZ_name);
	free(MM_name);
	free(NA_name);
	free(NP_name);
	free(NL_name);
	free(NI_name);
	free(NE_name);
	free(NG_name);
	free(MK_name);
	free(NO_name);
	free(OM_name);
	free(PK_name);
	free(PS_name);
	free(PA_name);
	free(PG_name);
	free(PY_name);
	free(PE_name);
	free(PL_name);
	free(PT_name);
	free(QA_name);
	free(RO_name);
	free(RU_name);
	free(RW_name);
	free(MF_name);
	free(SM_name);
	free(SA_name);
	free(SN_name);
	free(RS_name);
	free(SL_name);
	free(SX_name);
	free(SK_name);
	free(SI_name);
	free(SO_name);
	free(ZA_name);
	free(SS_name);
	free(ES_name);
	free(SD_name);
	free(SR_name);
	free(SE_name);
	free(CH_name);
	free(SY_name);
	free(TW_name);
	free(TJ_name);
	free(TZ_name);
	free(TH_name);
	free(TL_name);
	free(TG_name);
	free(TN_name);
	free(TR_name);
	free(TM_name);
	free(UG_name);
	free(UA_name);
	free(AE_name);
	free(GB_name);
	free(US_name);
	free(UM_name);
	free(UY_name);
	free(UZ_name);
	free(VE_name);
	free(VN_name);
	free(EH_name);
	free(YE_name);
	free(ZM_name);
	free(ZW_name);
	free(AF_alpha2);
	free(AL_alpha2);
	free(DZ_alpha2);
	free(AD_alpha2);
	free(AO_alpha2);
	free(AR_alpha2);
	free(AM_alpha2);
	free(AT_alpha2);
	free(AZ_alpha2);
	free(BD_alpha2);
	free(BY_alpha2);
	free(BE_alpha2);
	free(BZ_alpha2);
	free(BJ_alpha2);
	free(BT_alpha2);
	free(BO_alpha2);
	free(BA_alpha2);
	free(BW_alpha2);
	free(BR_alpha2);
	free(BN_alpha2);
	free(BG_alpha2);
	free(BF_alpha2);
	free(BI_alpha2);
	free(KH_alpha2);
	free(CM_alpha2);
	free(CA_alpha2);
	free(CF_alpha2);
	free(TD_alpha2);
	free(CL_alpha2);
	free(CN_alpha2);
	free(CO_alpha2);
	free(CG_alpha2);
	free(CD_alpha2);
	free(CR_alpha2);
	free(CI_alpha2);
	free(HR_alpha2);
	free(CZ_alpha2);
	free(DK_alpha2);
	free(DJ_alpha2);
	free(DO_alpha2);
	free(EC_alpha2);
	free(EG_alpha2);
	free(SV_alpha2);
	free(GQ_alpha2);
	free(ER_alpha2);
	free(EE_alpha2);
	free(SZ_alpha2);
	free(ET_alpha2);
	free(FI_alpha2);
	free(FR_alpha2);
	free(GF_alpha2);
	free(GA_alpha2);
	free(GM_alpha2);
	free(GE_alpha2);
	free(DE_alpha2);
	free(GH_alpha2);
	free(GI_alpha2);
	free(GR_alpha2);
	free(GT_alpha2);
	free(GN_alpha2);
	free(GW_alpha2);
	free(GY_alpha2);
	free(HT_alpha2);
	free(VA_alpha2);
	free(HN_alpha2);
	free(HK_alpha2);
	free(HU_alpha2);
	free(IN_alpha2);
	free(ID_alpha2);
	free(IR_alpha2);
	free(IQ_alpha2);
	free(IE_alpha2);
	free(IL_alpha2);
	free(IT_alpha2);
	free(JO_alpha2);
	free(KZ_alpha2);
	free(KE_alpha2);
	free(KP_alpha2);
	free(KR_alpha2);
	free(KW_alpha2);
	free(KG_alpha2);
	free(LA_alpha2);
	free(LV_alpha2);
	free(LB_alpha2);
	free(LS_alpha2);
	free(LR_alpha2);
	free(LY_alpha2);
	free(LI_alpha2);
	free(LT_alpha2);
	free(LU_alpha2);
	free(MO_alpha2);
	free(MW_alpha2);
	free(MY_alpha2);
	free(ML_alpha2);
	free(MR_alpha2);
	free(MX_alpha2);
	free(MD_alpha2);
	free(MC_alpha2);
	free(MN_alpha2);
	free(ME_alpha2);
	free(MA_alpha2);
	free(MZ_alpha2);
	free(MM_alpha2);
	free(NA_alpha2);
	free(NP_alpha2);
	free(NL_alpha2);
	free(NI_alpha2);
	free(NE_alpha2);
	free(NG_alpha2);
	free(MK_alpha2);
	free(NO_alpha2);
	free(OM_alpha2);
	free(PK_alpha2);
	free(PS_alpha2);
	free(PA_alpha2);
	free(PG_alpha2);
	free(PY_alpha2);
	free(PE_alpha2);
	free(PL_alpha2);
	free(PT_alpha2);
	free(QA_alpha2);
	free(RO_alpha2);
	free(RU_alpha2);
	free(RW_alpha2);
	free(MF_alpha2);
	free(SM_alpha2);
	free(SA_alpha2);
	free(SN_alpha2);
	free(RS_alpha2);
	free(SL_alpha2);
	free(SX_alpha2);
	free(SK_alpha2);
	free(SI_alpha2);
	free(SO_alpha2);
	free(ZA_alpha2);
	free(SS_alpha2);
	free(ES_alpha2);
	free(SD_alpha2);
	free(SR_alpha2);
	free(SE_alpha2);
	free(CH_alpha2);
	free(SY_alpha2);
	free(TW_alpha2);
	free(TJ_alpha2);
	free(TZ_alpha2);
	free(TH_alpha2);
	free(TL_alpha2);
	free(TG_alpha2);
	free(TN_alpha2);
	free(TR_alpha2);
	free(TM_alpha2);
	free(UG_alpha2);
	free(UA_alpha2);
	free(AE_alpha2);
	free(GB_alpha2);
	free(US_alpha2);
	free(UM_alpha2);
	free(UY_alpha2);
	free(UZ_alpha2);
	free(VE_alpha2);
	free(VN_alpha2);
	free(EH_alpha2);
	free(YE_alpha2);
	free(ZM_alpha2);
	free(ZW_alpha2);
}

void system_setup()
{
	// Set both screens to mode 0
	NF_Set2D(0, 0);
	NF_Set2D(1, 0);

	swiWaitForVBlank();

	// Initialize file system and set it as root folder
	nitroFSInit(NULL);
	NF_SetRootFolder("NITROFS");

	// Set both screens to mode 0
	NF_Set2D(0, 0);
	NF_Set2D(1, 0);

	// begin
	// Initialize tiled backgrounds system
    NF_InitTiledBgBuffers();    // Initialize storage buffers
    NF_InitTiledBgSys(0);       // Top screen
    // NF_InitTiledBgSys(1);       // Bottom screen

    // Initialize sprite system
    NF_InitSpriteBuffers();     // Initialize storage buffers
    NF_InitSpriteSys(0);        // Top screen
    NF_InitSpriteSys(1);        // Bottom screen

    // Load background files from NitroFS
    NF_LoadTiledBg("/bg/nfl", "nfl", 256, 256);
    NF_LoadTiledBg("/bg/bg3", "layer_3", 256, 256);
    NF_LoadTiledBg("/bg/bg2", "layer_2", 1024, 256);

    // Load sprite files from NitroFS
    NF_LoadSpriteGfx("/sprite/dot", 0, 2, 2);
    NF_LoadSpritePal("/sprite/dot", 0);

    // NF_LoadSpriteGfx("/sprite/ball", 1, 32, 32);
    // NF_LoadSpritePal("/sprite/ball", 1);

    // Create top screen background
    NF_CreateTiledBg(0, 3, "nfl");

    // Create bottom screen backgrounds
    // NF_CreateTiledBg(1, 3, "layer_3");
    // NF_CreateTiledBg(1, 2, "layer_2");

    // // Transfer the required sprites to VRAM
    NF_VramSpriteGfx(1, 0, 0, false); // Ball: Keep all frames in VRAM
    NF_VramSpritePal(1, 0, 0);

    // NF_VramSpriteGfx(0, 1, 0, false); // Character: Keep unused frames in RAM
    // NF_VramSpritePal(0, 1, 0);
}

void draw_console_pages(char pages[24][20][36], int item_selected, int page_selected)
{
	consoleClear();
	iprintf("%c.....\n", 'a' + page_selected);
	for (int i = 0; i < 20; i++)
	{
		if (item_selected == i)
		{
			iprintf(">");
		}
		if (strlen(pages[page_selected][i]) > 0)
			iprintf("%d. %s\n", i, pages[page_selected][i]);
	}
}

void draw_status_page(struct hash_table * alpha2_to_name, struct Vertex * source, struct Vertex * dest, struct Path * user_path)
{
	consoleClear();
	iprintf("CAMERA: X=%d, Y=%d\n", camera_x, camera_y);
	iprintf("%s --> %s\n" HLINE "\n", 
	dictionary_get_value(alpha2_to_name, source->s_data),
	dictionary_get_value(alpha2_to_name, dest->s_data));
	path_print(user_path);
}

void print_score(int pass, int par)
{
	if (pass)
	{
		iprintf("You won!\n");
		if (par > 0)
			iprintf("Perfect path!\n");
		else
			iprintf("You scored %d over par.\n", par);
	}
	else
		iprintf("You lost!\n");
}

/**
 * @brief Determines the position a sprite should be drawn on screen
 * based on camera position and sprite "world" position. Translates
 * a position in the imagined 2d plane, incl. space not drawn to a 
 * pixel position.
 * @param cx camera x
 * @param cy camera y
 * @param sx sprite x
 * @param sy sprite y
 * @param dx draw x
 * @param dy draw y 
 **/
void project(int cx, int cy, int sx, int sy, int * dx, int * dy)
{
    *dx = sx-cx;
    *dy = sy-cy;
}

void draw_demo_moving_sprite()
{
	int dx = 0, dy = 0;
	project(camera_x, camera_y, 100, 50, &dx, &dy);
	NF_MoveSprite(0, 5, dx, dy);
}

int spriteCoordinates[26][20][2] = {
    {
		// "AF:Afghanistan", 
		{0, 0},
	
		// "AL:Albania", 
		{0, 0},
	
		// "DZ:Algeria", 
		{0, 0},
		
		// "AD:Andorra",
		{0, 0},

		// "AO:Angola", 
		{0, 0},

		// "AR:Argentina", 
		{0, 0},

		// "AM:Armenia", 
		{0, 0},

		// "AT:Austria", 
		{0, 0},

		// "AZ:Azerbaijan" 
		{0, 0}

	},

	{
		// "Bahrain", 
		{0, 0},
		
		// "BD:Bangladesh",
		{0, 0},
		
		// "BY:Belarus",
		{0, 0},
		
		// "BE:Belgium",
		{0, 0},
		
		// "BZ:Belize", 
		{0, 0},
		
		//"BJ:Benin", 
		{0, 0},
		
		// BO:Bolivia",
		{0, 0},
		
		// "BA:Bosnia and Herzegovina", 
		{0, 0},
		
		// "BW:Botswana", 
		{0, 0},
		
		// "BR:Brazil", 
		{0, 0},
		
		// "BN:Brunei", 
		{0, 0},

		// "BG:Bulgaria", 
		{0, 0},
		
		// "BF:Burkina Faso",
		{0, 0},
		
		// "BI:Burundi"
		{0, 0},
	},

	{
		//"KH:Cambodia"
		{0, 0},
		//"CM:Cameroon"
		{0, 0},
		//"CA:Canada",
		{0, 0},
		//"CF:Central African Republic"
		{0, 0},
		//"TD:Chad"
		{0, 0},
		//"CL:Chile"
		{0, 0},
		//"CN:China"
		{0, 0},
		//"CO:Colombia",
		{0, 0},
		//"CR:Costa Rica"
		{0, 0},
		//"CI:Cote d'Ivoire"
		{0, 0},
		//"HR:Croatia"
		{0, 0},
		//"CZ:Czechia"
		{0, 0}
	},

	{
		//"CD:Democratic Republic of the Congo"
		{0, 0},
		//"DK:Denmark",
		{0, 0},
		//"DJ:Djibouti",
		{0, 0},
		//"DO:Dominican Republic"
		{0, 0}
	},

	{
		//"EC:Ecuador"
		{0, 0},
		//"EG:Egypt"
		{0, 0},
		//"SV:El Salvador",
		{0, 0},
		//"GQ:Equatorial Guinea"
		{0, 0},
		//"ER:Eritrea"
		{0, 0},
		//"EE:Estonia"
		{0, 0},
		//"SZ:Eswatini"
		{0, 0},
		//"ET:Ethiopia"
		{0, 0}
	},

	{
		//"FI:Finland"
		{0, 0},
		//"FR:France"
		{0, 0},
		//"GF:French Guiana"
		{0, 0}
	},

	{
		//"GA:Gabon"
		{0, 0},
		//"GM:Gambia"
		{0, 0},
		//"GE:Georgia"
		{0, 0},
		//"DE:Germany"
		{0, 0},
		//"GH:Ghana"
		{0, 0},
		//"GR:Greece"
		{0, 0},
		//"GT:Guatemala"
		{0, 0},
		//"GN:Guinea"
		{0, 0},
		//"GW:Guinea-Bissau"
		{0, 0},
		//"GY:Guyana"
		{0, 0}
	},

	{
		//"HT:Haiti"
		{0, 0},
		//"VA:Holy See"
		{0, 0},
		//"HN:Honduras"
		{0, 0},
		//"HU:Hungary"
		{0, 0}
	},

	{
		//"Iceland"
		{0, 0},
		//"IN:India"
		{0, 0},
		//"ID:Indonesia"
		{0, 0},
		//"IR:Iran"
		{0, 0},
		//"IQ:Iraq"
		{0, 0},
		//"IE:Ireland"
		{0, 0},
		//"IL:Israel"
		{0, 0},
		//"IT:Italy"
		{0, 0},
	},

	{
		//"JO:Jordan"
		{0, 0}
	},

	{
		//"KZ:Kazakhstan"
		{0, 0},
		//"KE:Kenya"
		{0, 0},
		//"Kosovo"
		{0, 0},
		//"KW:Kuwait"
		{0, 0},
		//"KG:Kyrgyzstan"
		{0, 0}
	},

	{
		//"LA:Laos"
		{0, 0},
		//"LV:Latvia"
		{0, 0},
		//"LB:Lebanon",
		{0, 0},
		//"Lesotho"
		{0, 0},
		//"LR:Liberia"
		{0, 0},
		//"LY:Libya"
		{0, 0},
		//"LI:Liechtenstein"
		{0, 0},
		// "LT:Lithuania"
		{0, 0},
		//"LU:Luxembourg"
		{0, 0},
	},
	// M
	{
		// "MO:Macao"
		{0, 0},
		//"MW:Malawi"
		{0, 0},
		//"MY:Malaysia",
		{0, 0},
		// "ML:Mali"
		{0, 0},
		//"MR:Mauritania"
		{0, 0},
		//"MX:Mexico"
		{0, 0},
		//"MD:Moldova"
		{0, 0},
		// "MC:Monaco"
		{0, 0},
		//"MN:Mongolia"
		{0, 0},
		//"ME:Montenegro"
		{0, 0},
		//"MA:Morocco"
		{0, 0},
		// "MZ:Mozambique"
		{0, 0}
	},
	// N
	{
		//"NA:Namibia"
		{0, 0},
		//"NP:Nepal"
		{0, 0},
		//"NL:Netherlands"
		{0, 0},
		// "NI:Nicaragua"
		{0, 0},
		//"NE:Niger"
		{0, 0},
		//"NG:Nigeria",
		{0, 0},
		//"MK:North Macedonia"
		{0, 0},
		//"KP:North Korea"
		{0, 0},
		//"NO:Norway"
		{0, 0},
	},
	// O
	{
		//"OM:Oman"
		{0, 0}
	},
	// P
	{
		//"PK:Pakistan"
		{0, 0},
		//"PS:Palestine"
		{0, 0},
		//"PA:Panama"
		{0, 0},
		//"PG:Papua New Guinea"
		{0, 0},
		//"PY:Paraguay",
		{0, 0},
		//"PE:Peru"
		{0, 0},
		//"PL:Poland"
		{0, 0},
		//"PT:Portugal"
		{0, 0}
	},
	// Q
	{
		// "QA:Qatar"
		{0, 0}
	},
	// R
	{
		// "CG:Republic of Congo"
		{0, 0},

		//"RO:Romania"
		{0, 0},
		
		//"RU:Russian Federation"
		{0, 0},
		
		// "RW:Rwanda"
		{0, 0}
	},

	// S
	{
		//"SM:San Marino"
		{0, 0},
		//"SA:Saudi Arabia"
		{0, 0},
		//"SN:Senegal",
		{0, 0},
		//"RS:Serbia"
		{0, 0},
		//"SL:Sierra Leone"
		{0, 0},
		//"SG:Singapore"
		{0, 0},
		//"SK:Slovakia",
		{0, 0},
		// "SI:Slovenia"
		{0, 0},
		//"SO:Somalia"
		{0, 0},
		//"ZA:South Africa"
		{0, 0},
		//"KR:South Korea",
		{0, 0},
		// "SS:South Sudan"
		{0, 0},
		//"ES:Spain"
		{0, 0},
		//"SD:Sudan",
		{0, 0},
		// "SR:Suriname"
		{0, 0},
		//"CH:Switzerland"
		{0, 0},
		//"SE:Sweden"
		{0, 0},
		//"SY:Syria"},
		{0, 0}
	},
	// T
	{
		// "TJ:Tajikistan"
		{0, 0},
		//"TZ:Tanzania"
		{0, 0},
		//"TH:Thailand"
		{0, 0},
		//"TL:Timor-Leste"
		{0, 0},
		//"TN:Tunisia"
		{0, 0},
		//"TR:Turkey"
		{0, 0},
		//"TM:Turkmenistan"},
		{0, 0}
	},
	// U
	{
		//"UG:Uganda"
		{0, 0},

		//"UA:Ukraine"
		{0, 0},
		
		//"AE:United Arab Emirates"
		{0, 0},
		
		//"GB:United Kingdom"
		{0, 0},
		
		//"UY:Uruguay"
		{0, 0},
		
		//"UZ:Uzbekistan"
		{0, 0},
		
		//"US:United States"},
		{0, 0},
	},
    // V
	{
		//"VE:Venezuela"
		{0, 0},
		//"VN:Vietnam"},
		{0, 0}
	},
	// NO W
	{},
	// NO X
	{},
	// Y
	{
		//"YE:Yemen"
		{0, 0}
	},
    // Z
	{
		//"ZM:Zambia"
		{0, 0},
		//"ZW:Zimbabwe"},
		{0, 0}
	}
};

char pages[26][20][36] = {
		
    {"AF:Afghanistan", "AL:Albania", "DZ:Algeria", "AD:Andorra",
	"AO:Angola", "AR:Argentina", "AM:Armenia", "AT:Austria", 
	"AZ:Azerbaijan"},

	{"Bahrain", "BD:Bangladesh",
	"BY:Belarus","BE:Belgium","BZ:Belize", "BJ:Benin", "BO:Bolivia", 
	"BA:Bosnia and Herzegovina", "BW:Botswana", "BR:Brazil", 
	"BN:Brunei", "BG:Bulgaria", "BF:Burkina Faso",
	"BI:Burundi"},

	{"KH:Cambodia", "CM:Cameroon", "CA:Canada",
	"CF:Central African Republic", "TD:Chad", 
	"CL:Chile", "CN:China", "CO:Colombia",
	"CR:Costa Rica", "CI:Cote d'Ivoire", "HR:Croatia", "CZ:Czechia"},

	{"CD:Democratic Republic of the Congo", "DK:Denmark",
	"DJ:Djibouti","DO:Dominican Republic"},

	{"EC:Ecuador", "EG:Egypt", "SV:El Salvador",
	"GQ:Equatorial Guinea", "ER:Eritrea", "EE:Estonia", 
	"SZ:Eswatini", "ET:Ethiopia"},

	{"FI:Finland", "FR:France", "GF:French Guiana"},

	{"GA:Gabon", "GM:Gambia", "GE:Georgia", "DE:Germany", 
	"GH:Ghana", "GR:Greece", "GT:Guatemala", "GN:Guinea", 
	"GW:Guinea-Bissau", "GY:Guyana"},

	{"HT:Haiti", "VA:Holy See", "HN:Honduras", "HU:Hungary"},

	{"Iceland", "IN:India", "ID:Indonesia", "IR:Iran", "IQ:Iraq", 
	"IE:Ireland", "IL:Israel", "IT:Italy"},

	{"JO:Jordan"},

	{"KZ:Kazakhstan", "KE:Kenya", "Kosovo", "KW:Kuwait", "KG:Kyrgyzstan"},

	{"LA:Laos", "LV:Latvia", "LB:Lebanon","Lesotho", 
	"LR:Liberia", "LY:Libya", "LI:Liechtenstein", 
	"LT:Lithuania", "LU:Luxembourg"},
	// M
	{"MO:Macao", "MW:Malawi", "MY:Malaysia",
	"ML:Mali", "MR:Mauritania", "MX:Mexico", "MD:Moldova", 
	"MC:Monaco", "MN:Mongolia", "ME:Montenegro", "MA:Morocco", 
	"MZ:Mozambique"},
	// N
	{"NA:Namibia", "NP:Nepal", "NL:Netherlands",
	"NI:Nicaragua", "NE:Niger", "NG:Nigeria",
	"MK:North Macedonia", "KP:North Korea", "NO:Norway"},
	// O
	{"OM:Oman"},
	// P
	{"PK:Pakistan", "PS:Palestine", 
	"PA:Panama", "PG:Papua New Guinea", "PY:Paraguay",
	"PE:Peru", "PL:Poland", "PT:Portugal"},
	// Q
	{"QA:Qatar"},
	// R
	{"CG:Republic of Congo", "RO:Romania", "RU:Russian Federation", 
	"RW:Rwanda"},

	// S
	{"SM:San Marino", "SA:Saudi Arabia", "SN:Senegal",
	"RS:Serbia", "SL:Sierra Leone", "SG:Singapore", "SK:Slovakia",
	"SI:Slovenia", "SO:Somalia", "ZA:South Africa", "KR:South Korea",
	"SS:South Sudan", "ES:Spain", "SD:Sudan",
	"SR:Suriname", "CH:Switzerland", "SE:Sweden", "SY:Syria"},
	// T
	{"TJ:Tajikistan", "TZ:Tanzania", "TH:Thailand", "TL:Timor-Leste", 
	"TN:Tunisia", "TR:Turkey", "TM:Turkmenistan"},
    // U
	{"UG:Uganda", "UA:Ukraine", "AE:United Arab Emirates", 
	"GB:United Kingdom", "UY:Uruguay", "UZ:Uzbekistan", "US:United States"},
    // V
	{"VE:Venezuela", "VN:Vietnam"},
    // NO W
	{},
	// NO X
	{},
	// Y
	{"YE:Yemen"},
    // Z
	{"ZM:Zambia", "ZW:Zimbabwe"},
	};

int main(void)
{
	// Set up 2-letter code -> country name dictionary
	struct hash_table * alpha2_to_name = dictionary_create(500);

	// Set up country name -> 2-letter code dictionary
	struct hash_table * name_to_alpha2 = dictionary_create(500);

	// Set up 2 letter code -> number dictionary
	struct hash_table *alpha2_to_numeric = dictionary_create(500);

	// Array of countries by number for lookup
	struct Vertex * countryVertices[895];
	memset(countryVertices, 0, sizeof(struct Vertex *) * 895);
	
	create_country_strings();
	populate_dictionaries(alpha2_to_name, name_to_alpha2, alpha2_to_numeric);
	create_country_vertices();
	create_country_edges();
	populate_vertex_array(countryVertices);

	// Set up random number generator.
	srand(time(NULL));

	// Starting point, destination, and generated path
	struct Vertex * source = NULL;
	struct Vertex * dest = NULL;
	struct Path * sys_path = NULL;
	struct Path * user_path = NULL;
	
	PrintConsole console;
	Keyboard kb;
	
	int keys = 0;

	system_setup();

	consoleInit(&console, 1, BgType_Text4bpp, BgSize_T_256x256, 18, 2, false, true); // bottom
	// consoleInit(&console, 0, BgType_Text4bpp, BgSize_T_256x256,  2, 0, true,  true); // top
	console.windowHeight = 24;

	keyboardInit(&kb, 0, BgType_Text4bpp, BgSize_T_256x512, 14, 0, false, true);
	kb.OnKeyPressed = OnKeyPressed;
	consoleSelect(&console);

	// Create ball sprite for test moves with project function.
	// NF_CreateSprite(0, 5, 1, 0, 100, 50);
	
	int running = 1;

	int num_pages = 26;
	int page_selected = 0;
	int item_selected = 0;

	
	enum GAME_STATE state = MAIN_MENU;

	int count = 0;
	int delay_count = 0;
	char * title = strdup(
		"================================\n"
		"=== W o r l d  .  P a t h    ===\n"
		"================================\n"
		"===   START:        NEW GAME ===\n"
		"=== DEV. BY:   AMCCOLM.CODES ===\n"
		"=== USING  :   LIBNDS, NFLIB ===\n"
		"=== TYVM<3 :     MIKA MYNETT ===\n"
		"=== PRESS B:    STATUS CHECK ===\n"
		"=== PRESS X:        END GAME ===\n"
		"=== PRESS Y:  SEE NEIGHBOURS ===\n"
		"===  SELECT:  ENTER PAN MODE ===\n"
		"=== B (PAN): BACK TO PLAYING ===\n"
		"================================\n"
	);
	char * c = title;

	while (running) // while game is active
	{
		NF_SpriteOamSet(0);
		NF_SpriteOamSet(1);

		oamUpdate(&oamMain);
		oamUpdate(&oamSub);

		scanKeys();
		keys = keysDown();

		// draw_demo_moving_sprite();

		if (state == WAITING)
		{
			if (keys & KEY_START)
				state = MAIN_MENU;
		}

		// If we are in the main menu, loop the animated printing title
		if (state == MAIN_MENU)
		{
			if (count == 5)
			{
				if (*c == '\0')
				{
					if (delay_count == 200)
					{
						c = title;
						consoleClear();
					}
					else
					{
						// iprintf(".");
						delay_count++;
					}
				}

				iprintf("%c", *c);
				c++;
				count = 0;
			}
			count++;
			if (keys & KEY_START)
				state = GENERATING;
		}

		// If the challenge needs to be generated..
		if (state == GENERATING)
		{
			consoleClear(); // Clear out the main menu
			// Pick 2 countries and construct a path until the path is valid.
			while (sys_path == NULL || (sys_path->length > 4))
			{
				source = random_country(countryVertices);
				dest = random_country(countryVertices);
				sys_path = find_path(source, dest);
				user_path = construct_path();
				path_insert(user_path, source->s_data);
			}
			// Draw the status
			draw_status_page(alpha2_to_name, source, dest, user_path);
			// Now change the state
			state = PLAYING;
		}

		if (state == PLAYING)
		{
			// If the player says they are done, go to the end screen
			if(keys & KEY_X)
			{		
				state = GAME_END;
			}

			// Check for switching pages
			if (keys & KEY_RIGHT)
			{
				page_selected += 1;
				page_selected %= num_pages;
				item_selected = 0;
				draw_console_pages(pages, item_selected, page_selected);
			}

			if (keys & KEY_LEFT)
			{
				page_selected -= 1;
				if (page_selected < 0) page_selected = num_pages - 1;
				page_selected %= num_pages;
				item_selected = 0;
				draw_console_pages(pages, item_selected, page_selected);
			}

			if (keys & KEY_DOWN)
			{
				item_selected = (item_selected + 1) % 20;
				draw_console_pages(pages, item_selected, page_selected);
			}

			if (keys & KEY_UP)
			{
				item_selected = item_selected > 0 ? item_selected - 1 : 19;
				draw_console_pages(pages, item_selected, page_selected);
			}

			if (keys & KEY_A)
			{
				char * country_code = calloc(3, sizeof(char));
				country_code[0] = pages[page_selected][item_selected][0];
				country_code[1] = pages[page_selected][item_selected][1];
				country_code[2] = '\0';
				iprintf("Added %s to the path!\n", country_code);
				path_insert(user_path, country_code);
				path_print(user_path);
			}

			// Status check
			if (keys & KEY_B)
			{
				draw_status_page(alpha2_to_name, source, dest, user_path);
			}

			// Hint
			if (keys & KEY_Y)
			{
				// Print the list of countries adjacent to the last in the path
				int curr_path_length = user_path->length - 1;
				char * last_in_path = user_path->vertices[curr_path_length];
				iprintf("%s is bordered by:\n", 
					dictionary_get_value(alpha2_to_name, last_in_path));
				// We have the Alpha2 of the current country
				// Get the number
				int number = atoi(dictionary_get_value(alpha2_to_numeric, last_in_path));

				// Use the number to get the vertex
				struct Vertex * v = countryVertices[number];

				// Iterate over the neighbours.
				for (int i = 0; i < v->n_neighbours; i++)
				{
					iprintf("%s\n", dictionary_get_value(alpha2_to_name, v->neighbours[i]->s_data));
				}
			}

			// switch to Panning mode
			if (keys & KEY_SELECT)
			{
				state = PANNING;
				iprintf("entered panning mode\n");
			}
		}

		if (state == PANNING)
		{
			// check for return to playing mode
			if (keys & KEY_B)
			{
				state = PLAYING;
				iprintf("exiting panning mode\n");
			}

			// Camera panning
			if (keys & KEY_RIGHT)
				camera_x++;

			if (keys & KEY_LEFT)
				camera_x--;

			if (keys & KEY_UP)
				camera_y--;

			if (keys & KEY_DOWN)
				camera_y++;
		}

		if (state == GAME_END)
		{
			sys_path = NULL;
			iprintf(HLINE "\n");

			int path_valid = validate_path(user_path, alpha2_to_numeric, countryVertices);

			int path_reaches = (user_path->vertices[user_path->length - 1][0] == dest->s_data[0]) &&
				(user_path->vertices[user_path->length - 1][1] == dest->s_data[1]);

			int passes = path_valid && path_reaches;
			int par = user_path->length - sys_path->length;
			
			print_score(passes, par);
				
			state = WAITING;
		}
		swiWaitForVBlank();
	}

	// Free all dyamic memory used
	dictionary_delete(alpha2_to_name);
	free(alpha2_to_name);
	free(name_to_alpha2);
	free(alpha2_to_numeric);
	free_strings();

	return 0;
}