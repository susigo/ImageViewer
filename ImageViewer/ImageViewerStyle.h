#pragma once
#include <qcolor.h>
#include <qmap.h>
#include <QFile>
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>

//the style of imageviewer
struct ImageViewerStyle
{
	QColor backgroundColor = QColor("#124523");
	QColor foregroundColor = QColor("#456858");

	int chess_width = 50;
	int chess_height = 50;
};

//the style of shape
struct ShapeStyle
{
	QColor borderColor = QColor("#aaccdd");
	QColor fillColor = QColor("#445566aa");
	QColor center_color = QColor("#757575");
	QColor control_color = QColor("#363636");
	int border_width = 1;
	double control_handle_size = 20;

};

class ImageViewerStyleManager
{
public:
	ImageViewerStyleManager()
	{

	}
	~ImageViewerStyleManager()
	{

	}

	void setConfigDir(const QString& config_dir)
	{
		m_config_full_name = config_dir + "/" + m_style_file_name;
		if (!QFile::exists(m_config_full_name))
		{
			saveToJson(m_config_full_name);
		}
		loadFromJson(m_config_full_name);
	}

	void loadFromJson(const QString& json_path)
	{
		QFile tmp_file(json_path);
		if (!tmp_file.open(QIODevice::ReadOnly | QIODevice::Text))
		{
			//return;
		}
		QJsonDocument j_doc = QJsonDocument::fromJson(tmp_file.readAll());
		QJsonObject j_obj = j_doc.object();

		if (j_obj.contains("view_style"))
		{
			m_cur_view_style = getImageViewerStyle(j_obj["view_style"].toObject());
		}
		if (j_obj.contains("shape_style"))
		{
			m_cur_shape_style = getShapeStyle(j_obj["shape_style"].toObject());
		}
		tmp_file.close();
	}
	void saveToJson(const QString& json_path)
	{
		QFile tmp_file(json_path);

		if (!tmp_file.open(QIODevice::ReadWrite | QIODevice::Text))
		{
			//return;
		}

		QJsonDocument j_doc;
		QJsonObject j_obj;

		j_obj.insert("view_style", getJsonFromImageViewerStyle(m_cur_view_style));
		j_obj.insert("shape_style", getJsonFromShapeStyle(m_cur_shape_style));
		j_doc.setObject(j_obj);

		tmp_file.write(j_doc.toJson());
		tmp_file.close();
	}

	QJsonObject getJsonFromImageViewerStyle(const ImageViewerStyle& style)
	{
		QJsonObject j_obj;
		j_obj.insert("background_color", style.backgroundColor.name());
		j_obj.insert("foreground_color", style.foregroundColor.name());
		j_obj.insert("chess_width", style.chess_width);
		j_obj.insert("chess_height", style.chess_height);
		return j_obj;
	}

	ImageViewerStyle getImageViewerStyle(const QJsonObject& j_obj)
	{
		ImageViewerStyle style;
		if (j_obj.contains("background_color"))
		{
			style.backgroundColor = QColor(j_obj["background_color"].toString());
		}
		if (j_obj.contains("foreground_color"))
		{
			style.foregroundColor = QColor(j_obj["foreground_color"].toString());
		}
		if (j_obj.contains("chess_width"))
		{
			style.chess_width = j_obj["chess_width"].toInt();
		}
		if (j_obj.contains("chess_height"))
		{
			style.chess_height = j_obj["chess_height"].toInt();
		}
		return style;
	}

	QJsonObject getJsonFromShapeStyle(const ShapeStyle& style)
	{
		QJsonObject j_obj;
		j_obj.insert("border_color", style.borderColor.name());
		j_obj.insert("fill_color", style.fillColor.name());
		j_obj.insert("center_color", style.center_color.name());
		j_obj.insert("control_color", style.control_color.name());
		j_obj.insert("border_width", style.border_width);
		j_obj.insert("control_handle_size", style.control_handle_size);
		return j_obj;
	}

	ShapeStyle getShapeStyle(const QJsonObject& j_obj)
	{
		ShapeStyle style;
		if (j_obj.contains("border_color"))
		{
			style.borderColor = QColor(j_obj["border_color"].toString());
		}
		if (j_obj.contains("fill_color"))
		{
			style.fillColor = QColor(j_obj["fill_color"].toString());
		}
		if (j_obj.contains("center_color"))
		{
			style.center_color = QColor(j_obj["center_color"].toString());
		}
		if (j_obj.contains("control_color"))
		{
			style.control_color = QColor(j_obj["control_color"].toString());
		}
		if (j_obj.contains("border_width"))
		{
			style.border_width = j_obj["border_width"].toInt();
		}
		if (j_obj.contains("control_handle_size"))
		{
			style.control_handle_size = j_obj["control_handle_size"].toDouble();
		}
		return style;
	}

	ImageViewerStyle getImageViewerStyle(const QString& style_name)
	{
		return m_cur_view_style;
		if (!m_view_style_map.contains(style_name))
		{
			return ImageViewerStyle();
		}
		return m_view_style_map[style_name];
	}
	ShapeStyle getShapeStyle(const QString& style_name)
	{
		return m_cur_shape_style;
		if (!m_shape_style_map.contains(style_name))
		{
			return ShapeStyle();
		}
		return m_shape_style_map[style_name];
	}

private:
	QMap<QString, ImageViewerStyle> m_view_style_map;
	QMap<QString, ShapeStyle> m_shape_style_map;

	ImageViewerStyle m_cur_view_style;
	ShapeStyle m_cur_shape_style;

	QString m_config_full_name;
	QString m_style_file_name = "ImageViewerStyle.json";
};