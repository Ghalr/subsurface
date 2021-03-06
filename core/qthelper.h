// SPDX-License-Identifier: GPL-2.0
#ifndef QTHELPER_H
#define QTHELPER_H

#include <stdint.h>
#include "dive.h"
#include "divelist.h"

// 1) Types

enum inertgas {N2, HE};

// 2) Functions visible only to C++ parts

#ifdef __cplusplus

#include <QMultiMap>
#include <QString>
#include <QTranslator>
#include <QDir>
QString weight_string(int weight_in_grams);
QString distance_string(int distanceInMeters);
bool gpsHasChanged(struct dive *dive, struct dive *master, const QString &gps_text, bool *parsed_out = 0);
QList<int> getDivesInTrip(dive_trip_t *trip);
QString get_gas_string(struct gasmix gas);
QString get_divepoint_gas_string(struct dive *d, const divedatapoint& dp);
QString get_taglist_string(struct tag_entry *tag_list);
void read_hashes();
void write_hashes();
void updateHash(struct picture *picture);
QByteArray hashFile(const QString &filename);
QString hashString(const char *filename);
QString thumbnailFileName(const QString &filename);
void learnImages(const QDir dir, int max_recursions);
void add_hash(const QString &filename, const QByteArray &hash);
void hashPicture(QString filename);
extern "C" char *hashstring(const char *filename);
QString localFilePath(const QString &originalFilename);
void learnHash(const QString &originalName, const QString &localName, const QByteArray &hash);
weight_t string_to_weight(const char *str);
depth_t string_to_depth(const char *str);
pressure_t string_to_pressure(const char *str);
volume_t string_to_volume(const char *str, pressure_t workp);
fraction_t string_to_fraction(const char *str);
int getCloudURL(QString &filename);
bool parseGpsText(const QString &gps_text, double *latitude, double *longitude);
QByteArray getCurrentAppState();
void setCurrentAppState(const QByteArray &state);
void init_proxy();
QString getUUID();
QStringList imageExtensionFilters();
char *intdup(int index);
char *copy_qstring(const QString &);
QString get_depth_string(depth_t depth, bool showunit = false, bool showdecimal = true);
QString get_depth_string(int mm, bool showunit = false, bool showdecimal = true);
QString get_depth_unit();
QString get_weight_string(weight_t weight, bool showunit = false);
QString get_weight_unit();
QString get_temperature_string(temperature_t temp, bool showunit = false);
QString get_temp_unit();
QString get_volume_string(volume_t volume, bool showunit = false);
QString get_volume_string(int mliter, bool showunit = false);
QString get_volume_unit();
QString get_pressure_string(pressure_t pressure, bool showunit = false);
QString get_pressure_unit();
QString getSubsurfaceDataPath(QString folderToFind);
QString getPrintingTemplatePathUser();
QString getPrintingTemplatePathBundle();
QString get_dc_nickname(const char *model, uint32_t deviceid);
int gettimezoneoffset(timestamp_t when = 0);
int parseDurationToSeconds(const QString &text);
int parseLengthToMm(const QString &text);
int parseTemperatureToMkelvin(const QString &text);
int parseWeightToGrams(const QString &text);
int parsePressureToMbar(const QString &text);
int parseGasMixO2(const QString &text);
int parseGasMixHE(const QString &text);
QString render_seconds_to_string(int seconds);
QString get_dive_duration_string(timestamp_t when, QString hoursText, QString minutesText, QString secondsText = QObject::tr("sec"), QString separator = ":", bool isFreeDive = false);
QString get_dive_surfint_string(timestamp_t when, QString daysText, QString hoursText, QString minutesText, QString separator = " ", int maxdays = 4);
QString get_dive_date_string(timestamp_t when);
QString get_short_dive_date_string(timestamp_t when);
bool is_same_day (timestamp_t trip_when, timestamp_t dive_when);
QString get_trip_date_string(timestamp_t when, int nr, bool getday);
QString uiLanguage(QLocale *callerLoc);
QLocale getLocale();
void selectedDivesGasUsed(QVector<QPair<QString, int> > &gasUsed);
QString getUserAgent();

#if defined __APPLE__
#define TITLE_OR_TEXT(_t, _m) "", _t + "\n" + _m
#else
#define TITLE_OR_TEXT(_t, _m) _t, _m
#endif

#endif

// 3) Functions visible to C and C++

#ifdef __cplusplus
extern "C" {
#endif

const char *printGPSCoords(int lat, int lon);
bool in_planner();
bool getProxyString(char **buffer);
bool canReachCloudServer();
void updateWindowTitle();
void subsurface_mkdir(const char *dir);
char *get_file_name(const char *fileName);
void copy_image_and_overwrite(const char *cfileName, const char *path, const char *cnewName);
char *hashstring(const char *filename);
void register_hash(const char *filename, const char *hash);
char *move_away(const char *path);
const char *local_file_path(struct picture *picture);
char *cloud_url();
char *hashfile_name_string();
char *picturedir_string();
const char *subsurface_user_agent();
enum deco_mode decoMode();
int parse_seabear_header(const char *filename, char **params, int pnr);
char *get_current_date();
double cache_value(int tissue, int timestep, enum inertgas gas);
void cache_insert(int tissue, int timestep, enum inertgas gas, double value);
void print_qt_versions();
void lock_planner();
void unlock_planner();

#ifdef __cplusplus
}
#endif

#endif // QTHELPER_H
