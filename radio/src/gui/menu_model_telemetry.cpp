/*
 * Authors (alphabetical order)
 * - Andre Bernet <bernet.andre@gmail.com>
 * - Andreas Weitl
 * - Bertrand Songis <bsongis@gmail.com>
 * - Bryan J. Rentoul (Gruvin) <gruvin@gmail.com>
 * - Cameron Weeks <th9xer@gmail.com>
 * - Erez Raviv
 * - Gabriel Birkus
 * - Jean-Pierre Parisy
 * - Karl Szmutny
 * - Michael Blandford
 * - Michal Hlavinka
 * - Pat Mackenzie
 * - Philip Moss
 * - Rob Thomson
 * - Thomas Husterer
 *
 * opentx is based on code named
 * gruvin9x by Bryan J. Rentoul: http://code.google.com/p/gruvin9x/,
 * er9x by Erez Raviv: http://code.google.com/p/er9x/,
 * and the original (and ongoing) project by
 * Thomas Husterer, th9x: http://code.google.com/p/th9x/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include "../opentx.h"

enum menuModelTelemetryItems {
  CASE_CPUARM(ITEM_TELEMETRY_PROTOCOL_TYPE)
#if !defined(CPUARM)
  ITEM_TELEMETRY_A1_LABEL,
  ITEM_TELEMETRY_A1_RANGE,
  ITEM_TELEMETRY_A1_OFFSET,
  ITEM_TELEMETRY_A1_ALARM1,
  ITEM_TELEMETRY_A1_ALARM2,
  ITEM_TELEMETRY_A2_LABEL,
  ITEM_TELEMETRY_A2_RANGE,
  ITEM_TELEMETRY_A2_OFFSET,
  ITEM_TELEMETRY_A2_ALARM1,
  ITEM_TELEMETRY_A2_ALARM2,
#endif
  ITEM_TELEMETRY_RSSI_LABEL,
  ITEM_TELEMETRY_RSSI_ALARM1,
  ITEM_TELEMETRY_RSSI_ALARM2,
#if defined(CPUARM)
  ITEM_TELEMETRY_SENSORS_LABEL,
  ITEM_TELEMETRY_SENSOR1,
  ITEM_TELEMETRY_SENSOR2,
  ITEM_TELEMETRY_SENSOR3,
  ITEM_TELEMETRY_SENSOR4,
  ITEM_TELEMETRY_SENSOR5,
  ITEM_TELEMETRY_SENSOR6,
  ITEM_TELEMETRY_SENSOR7,
  ITEM_TELEMETRY_SENSOR8,
  ITEM_TELEMETRY_SENSOR9,
  ITEM_TELEMETRY_SENSOR10,
  ITEM_TELEMETRY_SENSOR11,
  ITEM_TELEMETRY_SENSOR12,
  ITEM_TELEMETRY_SENSOR13,
  ITEM_TELEMETRY_SENSOR14,
  ITEM_TELEMETRY_SENSOR15,
  ITEM_TELEMETRY_SENSOR16,
#if defined(PCBTARANIS)
  ITEM_TELEMETRY_SENSOR17,
  ITEM_TELEMETRY_SENSOR18,
  ITEM_TELEMETRY_SENSOR19,
  ITEM_TELEMETRY_SENSOR20,
  ITEM_TELEMETRY_SENSOR21,
  ITEM_TELEMETRY_SENSOR22,
  ITEM_TELEMETRY_SENSOR23,
  ITEM_TELEMETRY_SENSOR24,
  ITEM_TELEMETRY_SENSOR25,
  ITEM_TELEMETRY_SENSOR26,
  ITEM_TELEMETRY_SENSOR27,
  ITEM_TELEMETRY_SENSOR28,
  ITEM_TELEMETRY_SENSOR29,
  ITEM_TELEMETRY_SENSOR30,
  ITEM_TELEMETRY_SENSOR31,
  ITEM_TELEMETRY_SENSOR32,
#endif
  ITEM_TELEMETRY_NEWSENSOR,
#endif
#if !defined(CPUARM)
#if defined(FRSKY_HUB) || defined(WS_HOW_HIGH)
  ITEM_TELEMETRY_USR_LABEL,
  ITEM_TELEMETRY_USR_PROTO,
  ITEM_TELEMETRY_USR_BLADES,
#endif
  ITEM_TELEMETRY_USR_VOLTAGE_SOURCE,
  ITEM_TELEMETRY_USR_CURRENT_SOURCE,
#if defined(FAS_OFFSET) || !defined(CPUM64)
  ITEM_TELEMETRY_FAS_OFFSET,
#endif
#endif
  CASE_VARIO(ITEM_TELEMETRY_VARIO_LABEL)
#if defined(VARIO)
  ITEM_TELEMETRY_VARIO_SOURCE,
#endif
  CASE_VARIO(ITEM_TELEMETRY_VARIO_RANGE)
#if defined(PCBTARANIS)
  ITEM_TELEMETRY_TOP_BAR_LABEL,
  ITEM_TELEMETRY_TOP_BAR_VOLTAGE,
  ITEM_TELEMETRY_TOP_BAR_ALTITUDE,
#endif
  ITEM_TELEMETRY_SCREEN_LABEL1,
  ITEM_TELEMETRY_SCREEN_LINE1,
  ITEM_TELEMETRY_SCREEN_LINE2,
  ITEM_TELEMETRY_SCREEN_LINE3,
  ITEM_TELEMETRY_SCREEN_LINE4,
  ITEM_TELEMETRY_SCREEN_LABEL2,
  ITEM_TELEMETRY_SCREEN_LINE5,
  ITEM_TELEMETRY_SCREEN_LINE6,
  ITEM_TELEMETRY_SCREEN_LINE7,
  ITEM_TELEMETRY_SCREEN_LINE8,
#if defined(CPUARM)
  ITEM_TELEMETRY_SCREEN_LABEL3,
  ITEM_TELEMETRY_SCREEN_LINE9,
  ITEM_TELEMETRY_SCREEN_LINE10,
  ITEM_TELEMETRY_SCREEN_LINE11,
  ITEM_TELEMETRY_SCREEN_LINE12,
  ITEM_TELEMETRY_SCREEN_LABEL4,
  ITEM_TELEMETRY_SCREEN_LINE13,
  ITEM_TELEMETRY_SCREEN_LINE14,
  ITEM_TELEMETRY_SCREEN_LINE15,
  ITEM_TELEMETRY_SCREEN_LINE16,
#endif
  ITEM_TELEMETRY_MAX
};

#if defined(FRSKY)
#if LCD_W >= 212
  #define TELEM_COL1        (1*FW)
  #define TELEM_COL2        (16*FW)
  #define TELEM_COL3        (28*FW)
  #define TELEM_BARS_COLMIN TELEM_COL2
  #define TELEM_BARS_COLMAX TELEM_COL3
  #define TELEM_SCRTYPE_COL TELEM_COL2
#else
  #define TELEM_COL1        INDENT_WIDTH
  #if defined(TRANSLATIONS_FR) || defined(TRANSLATIONS_CZ)
    #define TELEM_COL2      (9*FW)
  #else
    #define TELEM_COL2      (8*FW)
  #endif
  #define TELEM_BARS_COLMIN (56-3*FW)
  #define TELEM_BARS_COLMAX (14*FW-3)
  #define TELEM_SCRTYPE_COL TELEM_COL2
#endif

#define IS_RANGE_DEFINED(k) (g_model.frsky.channels[k].ratio > 0)

#if defined(PCBTARANIS)
  #define CHANNELS_ROWS
  #define SENSOR_ROWS(x)    (isTelemetryFieldAvailable(x) ? (uint8_t)0 : HIDDEN_ROW)
  #define SENSORS_ROWS      LABEL(Sensors), SENSOR_ROWS(0), SENSOR_ROWS(1), SENSOR_ROWS(2), SENSOR_ROWS(3), SENSOR_ROWS(4), SENSOR_ROWS(5), SENSOR_ROWS(6), SENSOR_ROWS(7), SENSOR_ROWS(8), SENSOR_ROWS(9), SENSOR_ROWS(10), SENSOR_ROWS(11), SENSOR_ROWS(12), SENSOR_ROWS(13), SENSOR_ROWS(14), SENSOR_ROWS(15), SENSOR_ROWS(16), SENSOR_ROWS(17), SENSOR_ROWS(18), SENSOR_ROWS(19), SENSOR_ROWS(20), SENSOR_ROWS(21), SENSOR_ROWS(22), SENSOR_ROWS(23), SENSOR_ROWS(24), SENSOR_ROWS(25), SENSOR_ROWS(26), SENSOR_ROWS(27), SENSOR_ROWS(28), SENSOR_ROWS(29), SENSOR_ROWS(30), SENSOR_ROWS(31), 0,
#elif defined(CPUARM)
  #define CHANNELS_ROWS
  #define SENSOR_ROWS(x)    (isTelemetryFieldAvailable(x) ? (uint8_t)0 : HIDDEN_ROW)
  #define SENSORS_ROWS      LABEL(Sensors), SENSOR_ROWS(0), SENSOR_ROWS(1), SENSOR_ROWS(2), SENSOR_ROWS(3), SENSOR_ROWS(4), SENSOR_ROWS(5), SENSOR_ROWS(6), SENSOR_ROWS(7), SENSOR_ROWS(8), SENSOR_ROWS(9), SENSOR_ROWS(10), SENSOR_ROWS(11), SENSOR_ROWS(12), SENSOR_ROWS(13), SENSOR_ROWS(14), SENSOR_ROWS(15), 0,
#else
  #define CHANNEL_ROWS(x)   LABEL(CHANNEL), 1, 0, 2, 2
  #define CHANNELS_ROWS     CHANNEL_ROWS(0), CHANNEL_ROWS(1),
  #define SENSORS_ROWS
#endif

#if defined(FAS_OFFSET) || !defined(CPUM64)
  #define IF_FAS_OFFSET(x)  x,
#else
  #define IF_FAS_OFFSET(x)
#endif

#if defined(CPUARM)
  #define USRDATA_ROWS
#elif defined(FRSKY_HUB) || defined(WS_HOW_HIGH)
  #define USRDATA_ROWS      LABEL(UsrData), 0, 0, 0, 0, IF_FAS_OFFSET(0)
#else
  #define USRDATA_ROWS      0, 0, IF_FAS_OFFSET(0)
#endif

#if defined(PCBTARANIS)
  #define RSSI_ROWS         LABEL(RSSI), 0, 0,
#else
  #define RSSI_ROWS         LABEL(RSSI), 1, 1,
#endif

#if defined(LUA)
  #define SCREEN_TYPE_ROWS  1
#elif defined(CPUARM) || defined(GAUGES)
  #define SCREEN_TYPE_ROWS  0
#else
  #define SCREEN_TYPE_ROWS  LABEL(SCREEN)
#endif

#if defined(PCBSTD)
  #define VARIO_RANGE_ROWS  1
#else
  #define VARIO_RANGE_ROWS  3
#endif

#if defined(PCBTARANIS)
  #define TELEMETRY_TYPE_ROWS  (g_model.moduleData[INTERNAL_MODULE].rfProtocol == RF_PROTO_OFF && g_model.externalModule == MODULE_TYPE_PPM) ? (uint8_t)0 : HIDDEN_ROW,
#elif defined(CPUARM)
  #define TELEMETRY_TYPE_ROWS  0,
#else
  #define TELEMETRY_TYPE_ROWS
#endif

#if defined(CPUARM)
  #if defined(LUA)
    #define TELEMETRY_SCREEN_LINE(x) ((TELEMETRY_SCREEN_TYPE(x) == TELEMETRY_SCREEN_TYPE_NONE || TELEMETRY_SCREEN_TYPE(x) == TELEMETRY_SCREEN_TYPE_SCRIPT) ? HIDDEN_ROW : (uint8_t)2)
  #else
    #define TELEMETRY_SCREEN_LINE(x) (TELEMETRY_SCREEN_TYPE(x) == TELEMETRY_SCREEN_TYPE_NONE ? HIDDEN_ROW : (uint8_t)2)
  #endif
  #define TELEMETRY_SCREEN_ROWS(x) SCREEN_TYPE_ROWS, TELEMETRY_SCREEN_LINE(x), TELEMETRY_SCREEN_LINE(x), TELEMETRY_SCREEN_LINE(x), TELEMETRY_SCREEN_LINE(x)
  #define TELEMETRY_CURRENT_EDIT_SCREEN(k) (k < ITEM_TELEMETRY_SCREEN_LABEL2 ? 0 : (k < ITEM_TELEMETRY_SCREEN_LABEL3 ? 1 : (k < ITEM_TELEMETRY_SCREEN_LABEL4 ? 2 : 3)))
#else
  #define TELEMETRY_SCREEN_ROWS(x) SCREEN_TYPE_ROWS, 2, 2, 2, 2
  #define TELEMETRY_CURRENT_EDIT_CHANNEL(k) (k >= ITEM_TELEMETRY_A2_LABEL ? TELEM_ANA_A2 : TELEM_ANA_A1)
#endif

#if defined(CPUARM)
enum SensorFields {
  SENSOR_FIELD_NAME,
  SENSOR_FIELD_TYPE,
  SENSOR_FIELD_ID,
  SENSOR_FIELD_FORMULA=SENSOR_FIELD_ID,
  SENSOR_FIELD_UNIT,
  SENSOR_FIELD_PRECISION,
  SENSOR_FIELD_PARAM1,
  SENSOR_FIELD_PARAM2,
  SENSOR_FIELD_PARAM3,
  SENSOR_FIELD_PARAM4,
  SENSOR_FIELD_INPUT_FLAGS,
  SENSOR_FIELD_LOGS,
  SENSOR_FIELD_MAX
};

bool isSensorUnit(int sensor, uint8_t unit)
{
  if (sensor == 0)
    return true;

  sensor -= 1;

  return g_model.telemetrySensors[sensor].unit == unit;
}

bool isCellsSensor(int sensor)
{
  return isSensorUnit(sensor, UNIT_CELLS);
}

bool isGPSSensor(int sensor)
{
  return isSensorUnit(sensor, UNIT_GPS);
}

bool isAltSensor(int sensor)
{
  return isSensorUnit(sensor, UNIT_DIST);
}

bool isVoltsSensor(int sensor)
{
  return isSensorUnit(sensor, UNIT_VOLTS);
}

bool isCurrentSensor(int sensor)
{
  return isSensorUnit(sensor, UNIT_AMPS);
}

bool isSensorAvailable(int sensor)
{
  if (sensor == 0)
    return true;
  else
    return isTelemetryFieldAvailable(abs(sensor) - 1);
}

#define SENSOR_2ND_COLUMN (12*FW)
#define SENSOR_3RD_COLUMN (18*FW)

#define SENSOR_UNIT_ROWS   (sensor->type == TELEM_TYPE_CALCULATED && sensor->formula >= TELEM_FORMULA_CELL) ? HIDDEN_ROW : ((sensor->unit == UNIT_GPS || sensor->unit == UNIT_DATETIME || sensor->unit == UNIT_CELLS) ? HIDDEN_ROW : (uint8_t)0)
#define SENSOR_PREC_ROWS   (sensor->type == TELEM_TYPE_CALCULATED && sensor->formula >= TELEM_FORMULA_CELL) ? HIDDEN_ROW : ((sensor->unit == UNIT_GPS || sensor->unit == UNIT_DATETIME) ? HIDDEN_ROW : (uint8_t)0)
#define SENSOR_PARAM1_ROWS (sensor->unit == UNIT_GPS || sensor->unit == UNIT_DATETIME || sensor->unit == UNIT_CELLS) ? HIDDEN_ROW : (uint8_t)0
#define SENSOR_PARAM2_ROWS (sensor->unit == UNIT_GPS || sensor->unit == UNIT_DATETIME || sensor->unit == UNIT_CELLS || (sensor->type==TELEM_TYPE_CALCULATED && sensor->formula==TELEM_FORMULA_CONSUMPTION)) ? HIDDEN_ROW : (uint8_t)0
#define SENSOR_PARAM3_ROWS (sensor->type == TELEM_TYPE_CALCULATED && sensor->formula < TELEM_FORMULA_MULTIPLY) ? (uint8_t)0 : HIDDEN_ROW
#define SENSOR_PARAM4_ROWS (sensor->type == TELEM_TYPE_CALCULATED && sensor->formula < TELEM_FORMULA_MULTIPLY) ? (uint8_t)0 : HIDDEN_ROW

void menuModelSensor(uint8_t event)
{
  TelemetrySensor * sensor = & g_model.telemetrySensors[s_currIdx];

  SUBMENU(STR_MENUSENSOR, SENSOR_FIELD_MAX, {0, 0, sensor->type == TELEM_TYPE_CALCULATED ? (uint8_t)0 : (uint8_t)1, SENSOR_UNIT_ROWS, SENSOR_PREC_ROWS, SENSOR_PARAM1_ROWS, SENSOR_PARAM2_ROWS, SENSOR_PARAM3_ROWS, SENSOR_PARAM4_ROWS, 0 });
  lcd_outdezAtt(PSIZE(TR_MENUSENSOR)*FW+1, 0, s_currIdx+1, INVERS|LEFT);

  putsTelemetryChannelValue(SENSOR_2ND_COLUMN, 0, s_currIdx, getValue(MIXSRC_FIRST_TELEM+3*s_currIdx), LEFT);

  int8_t sub = m_posVert;

  for (uint8_t i=0; i<LCD_LINES-1; i++) {
    coord_t y = MENU_TITLE_HEIGHT + 1 + i*FH;
    uint8_t k = i + s_pgOfs;

    for (int j=0; j<k; j++) {
      if (mstate_tab[j+1] == HIDDEN_ROW)
        k++;
    }

    uint8_t attr = (sub==k ? (s_editMode>0 ? BLINK|INVERS : INVERS) : 0);

    switch (k) {

      case SENSOR_FIELD_NAME:
        editSingleName(SENSOR_2ND_COLUMN, y, STR_NAME, sensor->label, TELEM_LABEL_LEN, event, attr);
        break;

      case SENSOR_FIELD_TYPE:
        sensor->type = selectMenuItem(SENSOR_2ND_COLUMN, y, STR_TYPE, "\012Custom\0   Calculated", sensor->type, 0, 1, attr, event);
        if (attr && checkIncDec_Ret) {
          sensor->instance = 0;
          if (sensor->type == TELEM_TYPE_CALCULATED) {
            sensor->param = 0;
            sensor->inputFlags = 0;
          }
        }
        break;

      case SENSOR_FIELD_ID:
        if (sensor->type == TELEM_TYPE_CUSTOM) {
          lcd_putsLeft(y, STR_ID);
          lcd_outhex4(SENSOR_2ND_COLUMN, y, sensor->id, LEFT|(m_posHorz==0 ? attr : 0));
          lcd_outdezAtt(SENSOR_3RD_COLUMN, y, sensor->instance, LEFT|(m_posHorz==1 ? attr : 0));
          if (attr) {
            switch (m_posHorz) {
              case 0:
                CHECK_INCDEC_MODELVAR_ZERO(event, sensor->id, 0xffff);
                break;

              case 1:
                CHECK_INCDEC_MODELVAR_ZERO(event, sensor->instance, 0xff);
                break;
            }
          }
        }
        else {
          sensor->formula = selectMenuItem(SENSOR_2ND_COLUMN, y, "Formula", "\010Add\0    Average\0Min\0    Max\0    MultiplyCell\0   ConsumptDistance", sensor->formula, 0, TELEM_FORMULA_DIST, attr, event);
          if (attr && checkIncDec_Ret) {
            sensor->param = 0;
            if (sensor->formula == TELEM_FORMULA_CELL) {
              sensor->unit = UNIT_VOLTS;
              sensor->prec = 2;
            }
            else if (sensor->formula == TELEM_FORMULA_DIST) {
              sensor->unit = UNIT_DIST;
              sensor->prec = 0;
            }
            else if (sensor->formula == TELEM_FORMULA_CONSUMPTION) {
              sensor->unit = UNIT_MAH;
              sensor->prec = 0;
            }
          }
        }
        break;

      case SENSOR_FIELD_UNIT:
        lcd_putsLeft(y, "Unit");
        // TODO flash saving with selectMenuItem where I copied those 2 lines?
        lcd_putsiAtt(SENSOR_2ND_COLUMN, y, STR_VTELEMUNIT, sensor->unit, attr);
        if (attr) {
          CHECK_INCDEC_MODELVAR_ZERO(event, sensor->unit, UNIT_MAX);
          if (checkIncDec_Ret) {
            telemetryItems[s_currIdx].clear();
          }
        }
        break;

      case SENSOR_FIELD_PRECISION:
        sensor->prec = selectMenuItem(SENSOR_2ND_COLUMN, y, STR_PRECISION, "\005PREC0PREC1PREC2", sensor->prec, 0, 2, attr, event);
        if (attr && checkIncDec_Ret) {
          telemetryItems[s_currIdx].clear();
        }
        break;

      case SENSOR_FIELD_PARAM1:
        if (sensor->type == TELEM_TYPE_CALCULATED) {
          if (sensor->formula == TELEM_FORMULA_CELL) {
            lcd_putsLeft(y, "Cells sensor");
            putsMixerSource(SENSOR_2ND_COLUMN, y, sensor->cell.source ? MIXSRC_FIRST_TELEM+3*(sensor->cell.source-1) : 0, attr);
            if (attr) {
              sensor->cell.source = checkIncDec(event, sensor->cell.source, 0, TELEM_VALUES_MAX, EE_MODEL|NO_INCDEC_MARKS, isCellsSensor);
            }
            break;
          }
          else if (sensor->formula == TELEM_FORMULA_DIST) {
            lcd_putsLeft(y, "GPS sensor");
            putsMixerSource(SENSOR_2ND_COLUMN, y, sensor->dist.gps ? MIXSRC_FIRST_TELEM+3*(sensor->dist.gps-1) : 0, attr);
            if (attr) {
              sensor->dist.gps = checkIncDec(event, sensor->dist.gps, 0, TELEM_VALUES_MAX, EE_MODEL|NO_INCDEC_MARKS, isGPSSensor);
            }
            break;
          }
          else if (sensor->formula == TELEM_FORMULA_CONSUMPTION) {
            lcd_putsLeft(y, "Amps sensor");
            putsMixerSource(SENSOR_2ND_COLUMN, y, sensor->consumption.source ? MIXSRC_FIRST_TELEM+3*(sensor->consumption.source-1) : 0, attr);
            if (attr) {
              sensor->consumption.source = checkIncDec(event, sensor->consumption.source, 0, TELEM_VALUES_MAX, EE_MODEL|NO_INCDEC_MARKS, isCurrentSensor);
            }
            break;
          }
        }
        else {
          lcd_putsLeft(y, "Ratio");
          if (attr) CHECK_INCDEC_MODELVAR(event, sensor->custom.ratio, 0, 30000);
          if (sensor->custom.ratio == 0)
            lcd_putcAtt(SENSOR_2ND_COLUMN, y, '-', attr);
          else
            lcd_outdezAtt(SENSOR_2ND_COLUMN, y, sensor->custom.ratio, LEFT|attr|PREC1);
          break;
        }
        // no break

      case SENSOR_FIELD_PARAM2:
        if (sensor->type == TELEM_TYPE_CALCULATED) {
          if (sensor->formula == TELEM_FORMULA_CELL) {
            sensor->cell.index = selectMenuItem(SENSOR_2ND_COLUMN, y, "Cell index", "\007Lowest\0001\0     2\0     3\0     4\0     5\0     6\0     HighestDelta\0", sensor->cell.index, 0, 8, attr, event);
            break;
          }
          else if (sensor->formula == TELEM_FORMULA_DIST) {
            lcd_putsLeft(y, "Alt sensor");
            putsMixerSource(SENSOR_2ND_COLUMN, y, sensor->dist.alt ? MIXSRC_FIRST_TELEM+3*(sensor->dist.alt-1) : 0, attr);
            if (attr) {
              sensor->dist.alt = checkIncDec(event, sensor->dist.alt, 0, TELEM_VALUES_MAX, EE_MODEL|NO_INCDEC_MARKS, isAltSensor);
            }
            break;
          }
        }
        else {
          lcd_putsLeft(y, NO_INDENT(STR_OFFSET));
          if (attr) CHECK_INCDEC_MODELVAR(event, sensor->custom.offset, -30000, +30000);
          if (sensor->prec > 0) attr |= (sensor->prec == 2 ? PREC2 : PREC1);
          lcd_outdezAtt(SENSOR_2ND_COLUMN, y, sensor->custom.offset, LEFT|attr);
          break;
        }
        // no break

      case SENSOR_FIELD_PARAM3:
        // no break

      case SENSOR_FIELD_PARAM4:
      {
        putsStrIdx(0, y, "Source", k-SENSOR_FIELD_PARAM1+1);
        int8_t & source = sensor->calc.sources[k-SENSOR_FIELD_PARAM1];
        if (attr) {
          source = checkIncDec(event, source, -TELEM_VALUES_MAX, TELEM_VALUES_MAX, EE_MODEL|NO_INCDEC_MARKS, isSensorAvailable);
        }
        if (source < 0) {
          lcd_putcAtt(SENSOR_2ND_COLUMN, y, '-', attr);
          putsMixerSource(lcdNextPos, y, MIXSRC_FIRST_TELEM+3*(-1-source), attr);
        }
        else {
          putsMixerSource(SENSOR_2ND_COLUMN, y, source ? MIXSRC_FIRST_TELEM+3*(source-1) : 0, attr);
        }
        break;
      }

      case SENSOR_FIELD_INPUT_FLAGS:
        sensor->inputFlags = selectMenuItem(SENSOR_2ND_COLUMN, y, "Options", "\013None\0      ""Auto Offset""Filter\0", sensor->inputFlags, 0, TELEM_INPUT_FLAGS_MAX, attr, event);
        break;

      case SENSOR_FIELD_LOGS:
        ON_OFF_MENU_ITEM(sensor->logs, SENSOR_2ND_COLUMN, y, "Logs", attr, event);
        break;

    }
  }
}

void onSensorMenu(const char *result)
{
  uint8_t index = m_posVert - 1 - ITEM_TELEMETRY_SENSOR1;

  if (index < TELEM_VALUES_MAX) {
    if (result == STR_EDIT) {
      pushMenu(menuModelSensor);
    }
    else if (result == STR_DELETE) {
      delTelemetryIndex(index);
      index += 1;
      if (index<TELEM_VALUES_MAX && isTelemetryFieldAvailable(index))
        m_posVert += 1;
      else
        m_posVert = 1+ITEM_TELEMETRY_NEWSENSOR;
    }
  }
}
#endif

#if defined(LUA)
void onTelemetryScriptFileSelectionMenu(const char *result)
{
  int8_t  sub = m_posVert - 1;
  uint8_t screenIndex = TELEMETRY_CURRENT_EDIT_SCREEN(sub);

  if (result == STR_UPDATE_LIST) {
    if (!listSdFiles(SCRIPTS_TELEM_PATH, SCRIPTS_EXT, sizeof(g_model.frsky.screens[screenIndex].script.file), NULL)) {
      POPUP_WARNING(STR_NO_SCRIPTS_ON_SD);
      s_menu_flags = 0;
    }
  }
  else {
    // The user choosed a file in the list
    memcpy(g_model.frsky.screens[screenIndex].script.file, result, sizeof(g_model.frsky.screens[screenIndex].script.file));
    eeDirty(EE_MODEL);
    LUA_LOAD_MODEL_SCRIPTS();
  }
}
#endif

void menuModelTelemetry(uint8_t event)
{
  MENU(STR_MENUTELEMETRY, menuTabModel, e_Telemetry, ITEM_TELEMETRY_MAX+1, {0, TELEMETRY_TYPE_ROWS CHANNELS_ROWS RSSI_ROWS SENSORS_ROWS USRDATA_ROWS CASE_VARIO(LABEL(Vario)) CASE_VARIO(0) CASE_VARIO(VARIO_RANGE_ROWS) CASE_PCBTARANIS(LABEL(TopBar)) CASE_PCBTARANIS(0) CASE_PCBTARANIS(0) TELEMETRY_SCREEN_ROWS(0), TELEMETRY_SCREEN_ROWS(1), CASE_CPUARM(TELEMETRY_SCREEN_ROWS(2)) CASE_CPUARM(TELEMETRY_SCREEN_ROWS(3))});

  uint8_t sub = m_posVert - 1;

#if !defined(PCBTARANIS)
  switch (event) {
    case EVT_KEY_BREAK(KEY_DOWN):
    case EVT_KEY_BREAK(KEY_UP):
    case EVT_KEY_BREAK(KEY_LEFT):
    case EVT_KEY_BREAK(KEY_RIGHT):
      if (s_editMode>0 && sub<=ITEM_TELEMETRY_RSSI_ALARM2)
        frskySendAlarms(); // update FrSky module when edit mode exited
      break;
  }
#endif

  for (uint8_t i=0; i<LCD_LINES-1; i++) {
    coord_t y = MENU_TITLE_HEIGHT + 1 + i*FH;
    uint8_t k = i + s_pgOfs;
#if defined(CPUARM)
    for (int j=0; j<=k; j++) {
      if (mstate_tab[j+1] == HIDDEN_ROW)
        k++;
    }
#endif

    uint8_t blink = ((s_editMode>0) ? BLINK|INVERS : INVERS);
    uint8_t attr = (sub == k ? blink : 0);

#if !defined(CPUARM)
    uint8_t ch = TELEMETRY_CURRENT_EDIT_CHANNEL(k);
    FrSkyChannelData & channel = g_model.frsky.channels[ch];
    uint8_t dest = TELEM_A1-1+ch;
#endif

#if defined(CPUARM)
    if (k>=ITEM_TELEMETRY_SENSOR1 && k<ITEM_TELEMETRY_SENSOR1+TELEM_VALUES_MAX) {
      int index = k-ITEM_TELEMETRY_SENSOR1;
      lcd_outdezAtt(INDENT_WIDTH, y, index+1, LEFT|attr);
      lcd_putcAtt(lcdLastPos, y, ':', attr);
      lcd_putsnAtt(3*FW, y, g_model.telemetrySensors[index].label, TELEM_LABEL_LEN, ZCHAR);
      if (telemetryItems[index].isFresh()) {
        lcd_putc(10*FW, y, '*');
      }
      TelemetryItem & telemetryItem = telemetryItems[index];
      if (telemetryItem.isAvailable()) {
        bool isOld = telemetryItem.isOld();
        lcdNextPos = TELEM_COL2;
        if (isOld) lcd_putc(lcdNextPos, y, '[');
        putsTelemetryChannelValue(lcdNextPos, y, index, getValue(MIXSRC_FIRST_TELEM+3*index), LEFT);
        if (isOld) lcd_putc(lcdLastPos, y, ']');
      }
      else {
        lcd_putsAtt(TELEM_COL2, y, "---", 0); // TODO shortcut
      }
      if (attr) {
        s_editMode = 0;
        s_currIdx = index;
        if (event == EVT_KEY_LONG(KEY_ENTER)) {
          killEvents(event);
          MENU_ADD_ITEM(STR_EDIT);
          MENU_ADD_ITEM(STR_DELETE);
          menuHandler = onSensorMenu;
        }
        else if (event == EVT_KEY_BREAK(KEY_ENTER)) {
          pushMenu(menuModelSensor);
        }
      }
    }
    else
#endif

    switch (k) {
#if defined(CPUARM)
      case ITEM_TELEMETRY_PROTOCOL_TYPE:
        g_model.telemetryProtocol = selectMenuItem(TELEM_COL2, y, STR_TELEMETRY_TYPE, "\017FrSky S.PORT\0  FrSky D\0       FrSky D (cable)", g_model.telemetryProtocol, PROTOCOL_TELEMETRY_FIRST, CASE_PCBTARANIS(g_eeGeneral.uart3Mode==UART_MODE_TELEMETRY ? PROTOCOL_FRSKY_D_SECONDARY : PROTOCOL_FRSKY_D) CASE_PCBSKY9X(PROTOCOL_FRSKY_D_SECONDARY) attr, event);
        break;
#endif

#if defined(CPUARM)
      case ITEM_TELEMETRY_SENSORS_LABEL:
        lcd_putsLeft(y, STR_TELEMETRY_SENSORS);
        break;

      case ITEM_TELEMETRY_NEWSENSOR:
        lcd_putsAtt(0, y, STR_TELEMETRY_NEWSENSOR, attr);
        if (attr && event==EVT_KEY_BREAK(KEY_ENTER)) {
          s_editMode = 0;
          int res = availableTelemetryIndex();
          if (res >= 0) {
            s_currIdx = res;
            pushMenu(menuModelSensor);
          }
        }
        break;
#endif

#if !defined(CPUARM)
      case ITEM_TELEMETRY_A1_LABEL:
      case ITEM_TELEMETRY_A2_LABEL:
        lcd_putsLeft(y, STR_ACHANNEL);
        lcd_outdezAtt(2*FW, y, ch+1, 0);
        putsTelemetryChannelValue(TELEM_COL2+6*FW, y, dest, frskyData.analog[ch].value, LEFT);
        break;

      case ITEM_TELEMETRY_A1_RANGE:
      case ITEM_TELEMETRY_A2_RANGE:
        lcd_putsLeft(y, STR_RANGE);
        putsTelemetryChannelValue(TELEM_COL2, y, dest, 255-channel.offset, (m_posHorz<=0 ? attr : 0)|NO_UNIT|LEFT);
        lcd_putsiAtt(lcdLastPos, y, STR_VTELEMUNIT, channel.type, m_posHorz!=0 ? attr : 0);
        if (attr && (s_editMode>0 || p1valdiff)) {
          if (m_posHorz == 0) {
            uint16_t ratio = checkIncDec(event, channel.ratio, 0, 256, EE_MODEL);
            if (checkIncDec_Ret) {
              if (ratio == 127 && channel.multiplier > 0) {
                channel.multiplier--; channel.ratio = 255;
              }
              else if (ratio == 256) {
                if (channel.multiplier < FRSKY_MULTIPLIER_MAX) { channel.multiplier++; channel.ratio = 128; }
              }
              else {
                channel.ratio = ratio;
              }
            }
          }
          else {
            CHECK_INCDEC_MODELVAR_ZERO(event, channel.type, UNIT_A1A2_MAX);
          }
        }
        break;

      case ITEM_TELEMETRY_A1_OFFSET:
      case ITEM_TELEMETRY_A2_OFFSET:
        lcd_putsLeft(y, STR_OFFSET);
        putsTelemetryChannelValue(TELEM_COL2, y, dest, 0, LEFT|attr);
        if (attr) channel.offset = checkIncDec(event, channel.offset, -256, 256, EE_MODEL);
        break;

      case ITEM_TELEMETRY_A1_ALARM1:
      case ITEM_TELEMETRY_A1_ALARM2:
      case ITEM_TELEMETRY_A2_ALARM1:
      case ITEM_TELEMETRY_A2_ALARM2:
      {
        uint8_t alarm = ((k==ITEM_TELEMETRY_A1_ALARM1 || k==ITEM_TELEMETRY_A2_ALARM1) ? 0 : 1);
        lcd_putsLeft(y, STR_ALARM);
        lcd_putsiAtt(TELEM_COL2, y, STR_VALARM, ALARM_LEVEL(ch, alarm), m_posHorz<=0 ? attr : 0);
        lcd_putsiAtt(TELEM_COL2+4*FW, y, STR_VALARMFN, ALARM_GREATER(ch, alarm), (CURSOR_ON_LINE() || m_posHorz==1) ? attr : 0);
        putsTelemetryChannelValue(TELEM_COL2+6*FW, y, dest, channel.alarms_value[alarm], ((CURSOR_ON_LINE() || m_posHorz==2) ? attr : 0) | LEFT);

        if (attr && (s_editMode>0 || p1valdiff)) {
          uint8_t t;
          switch (m_posHorz) {
           case 0:
             t = ALARM_LEVEL(ch, alarm);
             channel.alarms_level = (channel.alarms_level & ~(3<<(2*alarm))) + (checkIncDecModel(event, t, 0, 3) << (2*alarm));
             break;
           case 1:
             t = ALARM_GREATER(ch, alarm);
             if (t != checkIncDecModel(event, t, 0, 1)) {
               channel.alarms_greater ^= (1 << alarm);
               frskySendAlarms();
             }
             break;
           case 2:
             channel.alarms_value[alarm] = checkIncDec(event, channel.alarms_value[alarm], 0, 255, EE_MODEL);
             break;
          }
        }
        break;
      }
#endif

      case ITEM_TELEMETRY_RSSI_LABEL:
        lcd_putsLeft(y, PSTR("RSSI"));
        break;

      case ITEM_TELEMETRY_RSSI_ALARM1:
      case ITEM_TELEMETRY_RSSI_ALARM2: {
        uint8_t alarm = k-ITEM_TELEMETRY_RSSI_ALARM1;
#if defined(PCBTARANIS)
        lcd_putsLeft(y, (alarm==0 ? STR_LOWALARM : STR_CRITICALALARM));
        lcd_outdezNAtt(TELEM_COL2, y, getRssiAlarmValue(alarm), LEFT|attr, 3);
        if (attr && (s_editMode>0 || p1valdiff)) {
          CHECK_INCDEC_MODELVAR(event, g_model.frsky.rssiAlarms[alarm].value, -30, 30);
        }
#else
        lcd_putsLeft(y, STR_ALARM);
        lcd_putsiAtt(TELEM_COL2, y, STR_VALARM, ((2+alarm+g_model.frsky.rssiAlarms[alarm].level)%4), m_posHorz<=0 ? attr : 0);
        lcd_putc(TELEM_COL2+4*FW, y, '<');
        lcd_outdezNAtt(TELEM_COL2+6*FW, y, getRssiAlarmValue(alarm), LEFT|(m_posHorz!=0 ? attr : 0), 3);

        if (attr && (s_editMode>0 || p1valdiff)) {
          switch (m_posHorz) {
            case 0:
              CHECK_INCDEC_MODELVAR(event, g_model.frsky.rssiAlarms[alarm].level, -3, 2); // circular (saves flash)
              break;
            case 1:
              CHECK_INCDEC_MODELVAR(event, g_model.frsky.rssiAlarms[alarm].value, -30, 30);
              break;
          }
        }
#endif
        break;
      }

#if !defined(CPUARM)
#if defined(FRSKY_HUB) || defined(WS_HOW_HIGH)
      case ITEM_TELEMETRY_USR_LABEL:
        lcd_putsLeft(y, STR_USRDATA);
        break;

      case ITEM_TELEMETRY_USR_PROTO:
        lcd_putsLeft(y, STR_PROTO);
        lcd_putsiAtt(TELEM_COL2, y, STR_VTELPROTO, g_model.frsky.usrProto, attr);
        if (attr) CHECK_INCDEC_MODELVAR_ZERO(event, g_model.frsky.usrProto, USR_PROTO_LAST);
        break;

      case ITEM_TELEMETRY_USR_BLADES:
        lcd_putsLeft(y, STR_BLADES);
        lcd_outdezAtt(TELEM_COL2+FWNUM, y, 2+g_model.frsky.blades, attr);
        if (attr) CHECK_INCDEC_MODELVAR_ZERO(event, g_model.frsky.blades, MAX_BLADES);
        break;
#endif

      case ITEM_TELEMETRY_USR_VOLTAGE_SOURCE:
        lcd_putsLeft(y, STR_VOLTAGE);
        lcd_putsiAtt(TELEM_COL2, y, STR_AMPSRC, g_model.frsky.voltsSource+1, attr);
        if (attr) CHECK_INCDEC_MODELVAR_ZERO(event, g_model.frsky.voltsSource, FRSKY_VOLTS_SOURCE_LAST);
        break;

      case ITEM_TELEMETRY_USR_CURRENT_SOURCE:
        lcd_putsLeft(y, STR_CURRENT);
        lcd_putsiAtt(TELEM_COL2, y, STR_AMPSRC, g_model.frsky.currentSource, attr);
        if (attr) CHECK_INCDEC_MODELVAR_ZERO(event, g_model.frsky.currentSource, FRSKY_CURRENT_SOURCE_LAST);
        break;

#if defined(FAS_OFFSET) || !defined(CPUM64)
      case ITEM_TELEMETRY_FAS_OFFSET:
        lcd_putsLeft(y, STR_FAS_OFFSET);
        lcd_outdezAtt(TELEM_COL2, y, g_model.frsky.fasOffset, attr|LEFT|PREC1);
        lcd_outdezAtt(TELEM_COL2+6*FW, y, frskyData.hub.current, LEFT|PREC1);
        lcd_putc(TELEM_COL2+8*FW, y, 'A');
        if (attr) g_model.frsky.fasOffset = checkIncDec(event, g_model.frsky.fasOffset, -120, 120, EE_MODEL);
        break;
#endif
#endif

#if defined(VARIO)
      case ITEM_TELEMETRY_VARIO_LABEL:
        lcd_putsLeft(y, STR_VARIO);
        break;

      case ITEM_TELEMETRY_VARIO_SOURCE:
        lcd_putsLeft(y, STR_SOURCE);
#if defined(CPUARM)
        putsMixerSource(TELEM_COL2, y, g_model.frsky.varioSource ? MIXSRC_FIRST_TELEM+3*(g_model.frsky.varioSource-1) : 0, attr);
        if (attr) {
          g_model.frsky.varioSource = checkIncDec(event, g_model.frsky.varioSource, 0, TELEM_VALUES_MAX, EE_MODEL|NO_INCDEC_MARKS, isSensorAvailable);
        }
#else
        lcd_putsiAtt(TELEM_COL2, y, STR_VARIOSRC, g_model.frsky.varioSource, attr);
        if (attr) CHECK_INCDEC_MODELVAR(event, g_model.frsky.varioSource, 0, VARIO_SOURCE_LAST);
#endif
        break;

      case ITEM_TELEMETRY_VARIO_RANGE:
        lcd_putsLeft(y, STR_LIMIT);
#if defined(PCBSTD)
        lcd_outdezAtt(TELEM_COL2, y, 5+g_model.frsky.varioCenterMax, (m_posHorz==0 ? attr : 0)|PREC1|LEFT);
        lcd_outdezAtt(TELEM_COL2+8*FW, y, 10+g_model.frsky.varioMax, (m_posHorz==1 ? attr : 0));
        if (attr && (s_editMode>0 || p1valdiff)) {
          switch (m_posHorz) {
            case 0:
              CHECK_INCDEC_MODELVAR(event, g_model.frsky.varioCenterMax, -15, +15);
              break;
            case 1:
              CHECK_INCDEC_MODELVAR(event, g_model.frsky.varioMax, -7, 7);
              break;
          }
        }
#else
        lcd_outdezAtt(TELEM_COL2, y, -10+g_model.frsky.varioMin, (m_posHorz<=0 ? attr : 0)|LEFT);
        lcd_outdezAtt(TELEM_COL2+7*FW-2, y, -5+g_model.frsky.varioCenterMin, ((CURSOR_ON_LINE() || m_posHorz==1) ? attr : 0)|PREC1);
        lcd_outdezAtt(TELEM_COL2+10*FW, y, 5+g_model.frsky.varioCenterMax, ((CURSOR_ON_LINE() || m_posHorz==2) ? attr : 0)|PREC1);
        lcd_outdezAtt(TELEM_COL2+13*FW+2, y, 10+g_model.frsky.varioMax, ((CURSOR_ON_LINE() || m_posHorz==3) ? attr : 0));
        if (attr && (s_editMode>0 || p1valdiff)) {
          switch (m_posHorz) {
            case 0:
              CHECK_INCDEC_MODELVAR(event, g_model.frsky.varioMin, -7, 7);
              break;
            case 1:
              CHECK_INCDEC_MODELVAR(event, g_model.frsky.varioCenterMin, -16, 5+min<int8_t>(10, g_model.frsky.varioCenterMax+5));
              break;
            case 2:
              CHECK_INCDEC_MODELVAR(event, g_model.frsky.varioCenterMax, -5+max<int8_t>(-10, g_model.frsky.varioCenterMin-5), +15);
              break;
            case 3:
              CHECK_INCDEC_MODELVAR(event, g_model.frsky.varioMax, -7, 7);
              break;
          }
        }
#endif
        break;
#endif

#if defined(PCBTARANIS)
      case ITEM_TELEMETRY_TOP_BAR_LABEL:
        lcd_putsLeft(y, STR_TOP_BAR);
        break;

      case ITEM_TELEMETRY_TOP_BAR_VOLTAGE:
        lcd_putsLeft(y, STR_VOLTAGE);
        putsMixerSource(TELEM_COL2, y, g_model.frsky.voltsSource ? MIXSRC_FIRST_TELEM+3*(g_model.frsky.voltsSource-1) : 0, attr);
        if (attr) {
          g_model.frsky.voltsSource = checkIncDec(event, g_model.frsky.voltsSource, 0, TELEM_VALUES_MAX, EE_MODEL|NO_INCDEC_MARKS, isVoltsSensor);
        }
        break;

      case ITEM_TELEMETRY_TOP_BAR_ALTITUDE:
        lcd_putsLeft(y, STR_ALTITUDE);
        putsMixerSource(TELEM_COL2, y, g_model.frsky.altitudeSource ? MIXSRC_FIRST_TELEM+3*(g_model.frsky.altitudeSource-1) : 0, attr);
        if (attr) {
          g_model.frsky.altitudeSource = checkIncDec(event, g_model.frsky.altitudeSource, 0, TELEM_VALUES_MAX, EE_MODEL|NO_INCDEC_MARKS, isAltSensor);
        }
        break;
#endif

      case ITEM_TELEMETRY_SCREEN_LABEL1:
      case ITEM_TELEMETRY_SCREEN_LABEL2:
#if defined(CPUARM)
      case ITEM_TELEMETRY_SCREEN_LABEL3:
      case ITEM_TELEMETRY_SCREEN_LABEL4:
      {
        uint8_t screenIndex = TELEMETRY_CURRENT_EDIT_SCREEN(k);
        putsStrIdx(0*FW, y, STR_SCREEN, screenIndex+1);
        TelemetryScreenType oldScreenType = TELEMETRY_SCREEN_TYPE(screenIndex);
        TelemetryScreenType newScreenType = (TelemetryScreenType)selectMenuItem(TELEM_SCRTYPE_COL, y, PSTR(""), STR_VTELEMSCREENTYPE, oldScreenType, 0, TELEMETRY_SCREEN_TYPE_MAX, (m_posHorz==0 ? attr : 0), event);
        if (newScreenType != oldScreenType) {
          g_model.frsky.screensType = (g_model.frsky.screensType & (~(0x03 << (2*screenIndex)))) | (newScreenType << (2*screenIndex));
          memset(&g_model.frsky.screens[screenIndex], 0, sizeof(g_model.frsky.screens[screenIndex]));
        }
#if defined(LUA)
        if (newScreenType == TELEMETRY_SCREEN_TYPE_SCRIPT) {
          TelemetryScriptData & scriptData = g_model.frsky.screens[screenIndex].script;

          // TODO better function name for ---
          // TODO function for these lines
          if (ZEXIST(scriptData.file))
            lcd_putsnAtt(TELEM_SCRTYPE_COL+7*FW, y, scriptData.file, sizeof(scriptData.file), (m_posHorz==1 ? attr : 0));
          else
            lcd_putsiAtt(TELEM_SCRTYPE_COL+7*FW, y, STR_VCSWFUNC, 0, (m_posHorz==1 ? attr : 0));

          if (m_posHorz==1 && attr && event==EVT_KEY_BREAK(KEY_ENTER) && READ_ONLY_UNLOCKED()) {
            s_editMode = 0;
            if (listSdFiles(SCRIPTS_TELEM_PATH, SCRIPTS_EXT, sizeof(g_model.frsky.screens[screenIndex].script.file), g_model.frsky.screens[screenIndex].script.file)) {
              menuHandler = onTelemetryScriptFileSelectionMenu;
            }
            else {
              POPUP_WARNING(STR_NO_SCRIPTS_ON_SD);
              s_menu_flags = 0;
            }
          }
        }
        else if (attr) {
          MOVE_CURSOR_FROM_HERE();
        }
#endif
        break;
      }
#else
      {
        uint8_t screenIndex = (k < ITEM_TELEMETRY_SCREEN_LABEL2 ? 1 : 2);
        putsStrIdx(0*FW, y, STR_SCREEN, screenIndex);
#if defined(GAUGES)
        bool screenType = g_model.frsky.screensType & screenIndex;
        if (screenType != (bool)selectMenuItem(TELEM_SCRTYPE_COL, y, PSTR(""), STR_VTELEMSCREENTYPE, screenType, 0, 1, attr, event))
          g_model.frsky.screensType ^= screenIndex;
#endif
        break;
      }
#endif

      case ITEM_TELEMETRY_SCREEN_LINE1:
      case ITEM_TELEMETRY_SCREEN_LINE2:
      case ITEM_TELEMETRY_SCREEN_LINE3:
      case ITEM_TELEMETRY_SCREEN_LINE4:
      case ITEM_TELEMETRY_SCREEN_LINE5:
      case ITEM_TELEMETRY_SCREEN_LINE6:
      case ITEM_TELEMETRY_SCREEN_LINE7:
      case ITEM_TELEMETRY_SCREEN_LINE8:

#if defined(CPUARM)
      case ITEM_TELEMETRY_SCREEN_LINE9:
      case ITEM_TELEMETRY_SCREEN_LINE10:
      case ITEM_TELEMETRY_SCREEN_LINE11:
      case ITEM_TELEMETRY_SCREEN_LINE12:
      case ITEM_TELEMETRY_SCREEN_LINE13:
      case ITEM_TELEMETRY_SCREEN_LINE14:
      case ITEM_TELEMETRY_SCREEN_LINE15:
      case ITEM_TELEMETRY_SCREEN_LINE16:
#endif
      {
        uint8_t screenIndex, lineIndex;
        if (k < ITEM_TELEMETRY_SCREEN_LABEL2) {
          screenIndex = 0;
          lineIndex = k-ITEM_TELEMETRY_SCREEN_LINE1;
        }
#if defined(CPUARM)
        else if (k >= ITEM_TELEMETRY_SCREEN_LABEL4) {
          screenIndex = 3;
          lineIndex = k-ITEM_TELEMETRY_SCREEN_LINE13;
        }
        else if (k >= ITEM_TELEMETRY_SCREEN_LABEL3) {
          screenIndex = 2;
          lineIndex = k-ITEM_TELEMETRY_SCREEN_LINE9;
        }
#endif
        else {
          screenIndex = 1;
          lineIndex = k-ITEM_TELEMETRY_SCREEN_LINE5;
        }

#if defined(GAUGES)
        if (IS_BARS_SCREEN(screenIndex)) {
          FrSkyBarData & bar = g_model.frsky.screens[screenIndex].bars[lineIndex];
          source_t barSource = bar.source;
#if defined(CPUARM)
          putsMixerSource(TELEM_COL1, y, barSource, m_posHorz==0 ? attr : 0);
          if (barSource) {
            putsChannelValue(TELEM_BARS_COLMIN, y, barSource, bar.barMin, (m_posHorz==1 ? attr : 0) | LEFT);
            putsChannelValue(TELEM_BARS_COLMAX, y, barSource, bar.barMax, (m_posHorz==2 ? attr : 0) | LEFT);
          }
#else
          lcd_putsiAtt(TELEM_COL1, y, STR_VTELEMCHNS, barSource, m_posHorz==0 ? attr : 0);
          if (barSource) {
            putsTelemetryChannelValue(TELEM_BARS_COLMIN, y, barSource-1, convertBarTelemValue(barSource, bar.barMin), (m_posHorz==1 ? attr : 0) | LEFT);
            putsTelemetryChannelValue(TELEM_BARS_COLMAX, y, barSource-1, convertBarTelemValue(barSource, 255-bar.barMax), (m_posHorz==2 ? attr : 0) | LEFT);
          }
#endif
          else if (attr) {
            MOVE_CURSOR_FROM_HERE();
          }
          if (attr && (s_editMode>0 || p1valdiff)) {
            switch (m_posHorz) {
              case 0:
#if defined(CPUARM)
                bar.source = CHECK_INCDEC_MODELVAR_ZERO_CHECK(event, barSource, MIXSRC_LAST_TELEM, isSourceAvailable);
#else
                bar.source = CHECK_INCDEC_MODELVAR_ZERO(event, barSource, TELEM_DISPLAY_MAX);
#endif
                if (checkIncDec_Ret) {
                  bar.barMin = 0;
#if defined(CPUARM)
                  bar.barMax = 0;
#else
                  bar.barMax = 255 - maxBarTelemValue(bar.source);
#endif
                }
                break;
              case 1:
#if defined(CPUARM)
                bar.barMin = checkIncDec(event, bar.barMin, -30000, bar.barMax, EE_MODEL|NO_INCDEC_MARKS);
#else
                bar.barMin = checkIncDec(event, bar.barMin, 0, 254-bar.barMax, EE_MODEL|NO_INCDEC_MARKS);
#endif
                break;
              case 2:
#if defined(CPUARM)
                bar.barMax = checkIncDec(event, bar.barMax, bar.barMin, 30000, EE_MODEL|NO_INCDEC_MARKS);
#else
                bar.barMax = 255 - checkIncDec(event, 255-bar.barMax, bar.barMin+1, maxBarTelemValue(barSource), EE_MODEL|NO_INCDEC_MARKS);
#endif
                break;
            }
          }
        }
        else
#endif
        {
          for (uint8_t c=0; c<NUM_LINE_ITEMS; c++) {
            uint8_t cellAttr = (m_posHorz==c ? attr : 0);
            source_t & value = g_model.frsky.screens[screenIndex].lines[lineIndex].sources[c];
#if defined(PCBTARANIS)
            uint8_t pos[] = {TELEM_COL1, TELEM_COL2, TELEM_COL3};
#else
            uint8_t pos[] = {INDENT_WIDTH, TELEM_COL2};
#endif
#if defined(CPUARM)
            putsMixerSource(pos[c], y, value, cellAttr);
            if (cellAttr && (s_editMode>0 || p1valdiff)) {
              CHECK_INCDEC_MODELVAR_ZERO_CHECK(event, value, MIXSRC_LAST_TELEM, isSourceAvailable);
            }
#else
            lcd_putsiAtt(pos[c], y, STR_VTELEMCHNS, value, cellAttr);
            if (cellAttr && (s_editMode>0 || p1valdiff)) {
              CHECK_INCDEC_MODELVAR_ZERO_CHECK(event, value, (lineIndex==3 && c==0) ? TELEM_STATUS_MAX : TELEM_DISPLAY_MAX, isTelemetrySourceAvailable);
            }
#endif
          }
          if (attr && m_posHorz == NUM_LINE_ITEMS) {
            REPEAT_LAST_CURSOR_MOVE();
          }
        }
        break;
      }
    }
  }
}
#endif
