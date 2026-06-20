import 'dart:convert';
import 'package:flutter/material.dart';
import 'package:shared_preferences/shared_preferences.dart';

void main() {
  runApp(const DailyActivitiesRecorderApp());
}

class DailyActivitiesRecorderApp extends StatelessWidget {
  const DailyActivitiesRecorderApp({super.key});

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      title: 'Daily Activities Recorder',
      debugShowCheckedModeBanner: false,
      theme: ThemeData(
        colorScheme: ColorScheme.fromSeed(seedColor: const Color(0xFF13294B)),
        useMaterial3: true,
      ),
      home: const ActivitiesScreen(),
    );
  }
}

class ActivitiesScreen extends StatefulWidget {
  const ActivitiesScreen({super.key});

  @override
  State<ActivitiesScreen> createState() => _ActivitiesScreenState();
}

class _ActivitiesScreenState extends State<ActivitiesScreen> {
  final TextEditingController _searchController = TextEditingController();
  String _searchQuery = '';

  List<Map<String, String>> _activities = [];

  @override
  void initState() {
    super.initState();
    _loadActivities();
    _searchController.addListener(() {
      setState(() {
        _searchQuery = _searchController.text;
      });
    });
  }

  Future<void> _loadActivities() async {
    final prefs = await SharedPreferences.getInstance();
    final String? activitiesJson = prefs.getString('activities_list');
    if (activitiesJson != null) {
      final List<dynamic> decoded = json.decode(activitiesJson);
      setState(() {
        _activities = decoded
            .map((item) => Map<String, String>.from(item))
            .toList();
      });
    }
  }

  Future<void> _saveActivities() async {
    final prefs = await SharedPreferences.getInstance();
    final String activitiesJson = json.encode(_activities);
    await prefs.setString('activities_list', activitiesJson);
  }

  @override
  void dispose() {
    _searchController.dispose();
    super.dispose();
  }

  List<Map<String, String>> get _filteredActivities {
    if (_searchQuery.isEmpty) return _activities.reversed.toList();
    return _activities
        .where((activity) {
          final nameMatches = activity['name']!.toLowerCase().contains(
            _searchQuery.toLowerCase(),
          );
          final catMatches = activity['category']!.toLowerCase().contains(
            _searchQuery.toLowerCase(),
          );
          return nameMatches || catMatches;
        })
        .toList()
        .reversed
        .toList();
  }

  void _deleteActivity(Map<String, String> activity) {
    setState(() {
      _activities.remove(activity);
    });
    _saveActivities();
  }

  void _showActivityForm({Map<String, String>? activityToEdit}) {
    final TextEditingController nameController = TextEditingController(
      text: activityToEdit?['name'] ?? '',
    );
    final TextEditingController descController = TextEditingController(
      text: activityToEdit?['desc'] ?? '',
    );
    final TextEditingController dateController = TextEditingController(
      text: activityToEdit?['date'] ?? '',
    );
    final TextEditingController timeController = TextEditingController(
      text: activityToEdit?['time'] ?? '',
    );

    final List<String> predefinedCategories = [
      'Work',
      'Study',
      'Health',
      'Personal',
      'Exercise',
      'Other',
    ];

    String currentCat = activityToEdit?['category'] ?? 'Work';
    String selectedDropdown = predefinedCategories.contains(currentCat)
        ? currentCat
        : 'Other';

    final TextEditingController customCategoryController =
        TextEditingController(
          text: selectedDropdown == 'Other' ? currentCat : '',
        );

    showModalBottomSheet(
      context: context,
      isScrollControlled: true,
      backgroundColor: Colors.white,
      shape: const RoundedRectangleBorder(
        borderRadius: BorderRadius.vertical(top: Radius.circular(24)),
      ),
      builder: (context) {
        return StatefulBuilder(
          builder: (BuildContext context, StateSetter setModalState) {
            return Padding(
              padding: EdgeInsets.only(
                bottom: MediaQuery.of(context).viewInsets.bottom,
                left: 24,
                right: 24,
                top: 24,
              ),
              child: SingleChildScrollView(
                child: Column(
                  mainAxisSize: MainAxisSize.min,
                  crossAxisAlignment: CrossAxisAlignment.stretch,
                  children: [
                    Text(
                      activityToEdit == null
                          ? 'Add New Activity'
                          : 'Edit Activity',
                      style: const TextStyle(
                        fontSize: 22,
                        fontWeight: FontWeight.bold,
                        color: Color(0xFF0F1A3A),
                      ),
                      textAlign: TextAlign.center,
                    ),
                    const SizedBox(height: 24),
                    _buildTextField(
                      nameController,
                      'Activity name (e.g. Study) *',
                      Icons.title,
                    ),
                    const SizedBox(height: 16),
                    Row(
                      children: [
                        Expanded(
                          child: _buildTextField(
                            dateController,
                            'Select Date',
                            Icons.calendar_today,
                            readOnly: true,
                            onTap: () async {
                              DateTime? picked = await showDatePicker(
                                context: context,
                                initialDate: DateTime.now(),
                                firstDate: DateTime(2000),
                                lastDate: DateTime(2101),
                              );
                              if (picked != null) {
                                setModalState(() {
                                  dateController.text =
                                      "${picked.day}/${picked.month}/${picked.year}";
                                });
                              }
                            },
                          ),
                        ),
                        const SizedBox(width: 16),
                        Expanded(
                          child: _buildTextField(
                            timeController,
                            'Select Time',
                            Icons.access_time,
                            readOnly: true,
                            onTap: () async {
                              TimeOfDay? picked = await showTimePicker(
                                context: context,
                                initialTime: TimeOfDay.now(),
                              );
                              if (picked != null) {
                                setModalState(() {
                                  timeController.text = picked.format(context);
                                });
                              }
                            },
                          ),
                        ),
                      ],
                    ),
                    const SizedBox(height: 16),
                    DropdownButtonFormField<String>(
                      value: selectedDropdown,
                      decoration: InputDecoration(
                        prefixIcon: const Icon(
                          Icons.category,
                          color: Colors.blueGrey,
                          size: 20,
                        ),
                        contentPadding: const EdgeInsets.symmetric(
                          horizontal: 16,
                          vertical: 16,
                        ),
                        filled: true,
                        fillColor: Colors.grey.shade50,
                        enabledBorder: OutlineInputBorder(
                          borderRadius: BorderRadius.circular(12.0),
                          borderSide: BorderSide(color: Colors.grey.shade300),
                        ),
                        focusedBorder: OutlineInputBorder(
                          borderRadius: BorderRadius.circular(12.0),
                          borderSide: const BorderSide(
                            color: Color(0xFF0F1A3A),
                            width: 2,
                          ),
                        ),
                      ),
                      items: predefinedCategories.map((String category) {
                        return DropdownMenuItem(
                          value: category,
                          child: Text(category),
                        );
                      }).toList(),
                      onChanged: (String? newValue) {
                        if (newValue != null) {
                          setModalState(() {
                            selectedDropdown = newValue;
                            if (selectedDropdown != 'Other') {
                              customCategoryController.clear();
                            }
                          });
                        }
                      },
                    ),
                    if (selectedDropdown == 'Other') ...[
                      const SizedBox(height: 12),
                      _buildTextField(
                        customCategoryController,
                        'Please specify category...',
                        Icons.edit,
                      ),
                    ],
                    const SizedBox(height: 16),
                    _buildTextField(
                      descController,
                      'Description details...',
                      Icons.description,
                      maxLines: 3,
                    ),
                    const SizedBox(height: 24),
                    ElevatedButton(
                      onPressed: () {
                        if (nameController.text.trim().isEmpty) {
                          ScaffoldMessenger.of(context).showSnackBar(
                            const SnackBar(
                              content: Text('Activity name is required!'),
                            ),
                          );
                          return;
                        }

                        String finalCategory = selectedDropdown;
                        if (selectedDropdown == 'Other') {
                          finalCategory = customCategoryController.text.trim();
                          if (finalCategory.isEmpty) {
                            finalCategory = 'Other';
                          }
                        }

                        setState(() {
                          final newAct = {
                            'name': nameController.text.trim(),
                            'date': dateController.text.trim().isEmpty
                                ? 'Today'
                                : dateController.text.trim(),
                            'time': timeController.text.trim().isEmpty
                                ? '--:--'
                                : timeController.text.trim(),
                            'category': finalCategory,
                            'desc': descController.text.trim(),
                          };

                          if (activityToEdit == null) {
                            _activities.add(newAct);
                          } else {
                            final index = _activities.indexOf(activityToEdit);
                            if (index != -1) {
                              _activities[index] = newAct;
                            }
                          }
                        });
                        _saveActivities();
                        Navigator.pop(context);
                      },
                      style: ElevatedButton.styleFrom(
                        backgroundColor: const Color(0xFF0F1A3A),
                        foregroundColor: Colors.white,
                        padding: const EdgeInsets.symmetric(vertical: 16),
                        elevation: 2,
                        shape: RoundedRectangleBorder(
                          borderRadius: BorderRadius.circular(12),
                        ),
                      ),
                      child: Text(
                        activityToEdit == null
                            ? 'Save Activity'
                            : 'Update Activity',
                        style: const TextStyle(
                          fontSize: 16,
                          fontWeight: FontWeight.bold,
                          letterSpacing: 0.5,
                        ),
                      ),
                    ),
                    const SizedBox(height: 30),
                  ],
                ),
              ),
            );
          },
        );
      },
    );
  }

  Widget _buildTextField(
    TextEditingController controller,
    String hint,
    IconData icon, {
    int maxLines = 1,
    bool readOnly = false,
    VoidCallback? onTap,
  }) {
    return TextField(
      controller: controller,
      maxLines: maxLines,
      readOnly: readOnly,
      onTap: onTap,
      decoration: InputDecoration(
        prefixIcon: Icon(icon, color: Colors.blueGrey, size: 20),
        hintText: hint,
        hintStyle: const TextStyle(color: Colors.black54, fontSize: 14),
        contentPadding: const EdgeInsets.symmetric(
          horizontal: 16,
          vertical: 16,
        ),
        filled: true,
        fillColor: Colors.grey.shade50,
        enabledBorder: OutlineInputBorder(
          borderRadius: BorderRadius.circular(12.0),
          borderSide: BorderSide(color: Colors.grey.shade300),
        ),
        focusedBorder: OutlineInputBorder(
          borderRadius: BorderRadius.circular(12.0),
          borderSide: const BorderSide(color: Color(0xFF0F1A3A), width: 2),
        ),
      ),
    );
  }

  @override
  Widget build(BuildContext context) {
    const primaryDarkColor = Color(0xFF0F1A3A);
    final displayedActivities = _filteredActivities;

    return Scaffold(
      backgroundColor: Colors.grey.shade100,
      appBar: AppBar(
        backgroundColor: primaryDarkColor,
        elevation: 0,
        leading: const Icon(Icons.dashboard_rounded, color: Colors.white),
        title: const Text(
          'Dashboard',
          style: TextStyle(
            color: Colors.white,
            fontWeight: FontWeight.bold,
            fontSize: 22,
            letterSpacing: 0.5,
          ),
        ),
        centerTitle: false,
      ),
      body: Column(
        children: [
          Container(
            color: primaryDarkColor,
            padding: const EdgeInsets.fromLTRB(20, 10, 20, 25),
            child: TextField(
              controller: _searchController,
              style: const TextStyle(color: Colors.white),
              decoration: InputDecoration(
                hintText: 'Search activities...',
                hintStyle: const TextStyle(color: Colors.white70),
                prefixIcon: const Icon(Icons.search, color: Colors.white70),
                filled: true,
                fillColor: Colors.white.withOpacity(0.15),
                contentPadding: const EdgeInsets.symmetric(vertical: 0),
                border: OutlineInputBorder(
                  borderRadius: BorderRadius.circular(30),
                  borderSide: BorderSide.none,
                ),
              ),
            ),
          ),

          Expanded(
            child: displayedActivities.isEmpty
                ? Center(
                    child: Column(
                      mainAxisAlignment: MainAxisAlignment.center,
                      children: [
                        Icon(
                          Icons.event_note_rounded,
                          size: 72,
                          color: Colors.grey.shade300,
                        ),
                        const SizedBox(height: 16),
                        Text(
                          _searchQuery.isEmpty
                              ? 'No activities found.\nTap + to add one!'
                              : 'No matches found.',
                          textAlign: TextAlign.center,
                          style: TextStyle(
                            color: Colors.grey.shade500,
                            fontSize: 16,
                            fontWeight: FontWeight.w500,
                          ),
                        ),
                      ],
                    ),
                  )
                : ListView.builder(
                    padding: const EdgeInsets.all(16),
                    itemCount: displayedActivities.length,
                    itemBuilder: (context, index) {
                      final activity = displayedActivities[index];
                      return Card(
                        margin: const EdgeInsets.only(bottom: 16),
                        elevation: 1.5,
                        shadowColor: Colors.black12,
                        color: Colors.white,
                        surfaceTintColor: Colors.transparent,
                        shape: RoundedRectangleBorder(
                          borderRadius: BorderRadius.circular(16),
                        ),
                        child: Padding(
                          padding: const EdgeInsets.all(16),
                          child: Row(
                            crossAxisAlignment: CrossAxisAlignment.start,
                            children: [
                              Container(
                                padding: const EdgeInsets.all(12),
                                decoration: BoxDecoration(
                                  color: Colors.indigo.shade50,
                                  shape: BoxShape.circle,
                                ),
                                child: Icon(
                                  Icons.local_activity_rounded,
                                  color: Colors.indigo.shade400,
                                  size: 24,
                                ),
                              ),
                              const SizedBox(width: 16),
                              Expanded(
                                child: Column(
                                  crossAxisAlignment: CrossAxisAlignment.start,
                                  children: [
                                    Row(
                                      mainAxisAlignment:
                                          MainAxisAlignment.spaceBetween,
                                      children: [
                                        Expanded(
                                          child: Text(
                                            activity['name']!,
                                            style: const TextStyle(
                                              fontSize: 18,
                                              fontWeight: FontWeight.bold,
                                              color: primaryDarkColor,
                                            ),
                                          ),
                                        ),
                                        Container(
                                          padding: const EdgeInsets.symmetric(
                                            horizontal: 10,
                                            vertical: 4,
                                          ),
                                          decoration: BoxDecoration(
                                            color: Colors.orange.shade50,
                                            borderRadius: BorderRadius.circular(
                                              8,
                                            ),
                                          ),
                                          child: Text(
                                            activity['category']!,
                                            style: TextStyle(
                                              fontSize: 12,
                                              color: Colors.orange.shade800,
                                              fontWeight: FontWeight.bold,
                                              letterSpacing: 0.5,
                                            ),
                                          ),
                                        ),
                                      ],
                                    ),
                                    const SizedBox(height: 6),
                                    Row(
                                      children: [
                                        const Icon(
                                          Icons.calendar_month_rounded,
                                          size: 14,
                                          color: Colors.blueGrey,
                                        ),
                                        const SizedBox(width: 4),
                                        Text(
                                          '${activity['date']} • ${activity['time']}',
                                          style: const TextStyle(
                                            fontSize: 13,
                                            color: Colors.blueGrey,
                                            fontWeight: FontWeight.w600,
                                          ),
                                        ),
                                      ],
                                    ),
                                    if (activity['desc']!.isNotEmpty) ...[
                                      const SizedBox(height: 10),
                                      Text(
                                        activity['desc']!,
                                        style: const TextStyle(
                                          fontSize: 14,
                                          color: Colors.black87,
                                          height: 1.3,
                                        ),
                                      ),
                                    ],
                                    const SizedBox(height: 14),
                                    Row(
                                      mainAxisAlignment: MainAxisAlignment.end,
                                      children: [
                                        InkWell(
                                          onTap: () => _showActivityForm(
                                            activityToEdit: activity,
                                          ),
                                          borderRadius: BorderRadius.circular(
                                            4,
                                          ),
                                          child: const Padding(
                                            padding: EdgeInsets.symmetric(
                                              horizontal: 8,
                                              vertical: 4,
                                            ),
                                            child: Text(
                                              'EDIT',
                                              style: TextStyle(
                                                color: Colors.blueAccent,
                                                fontWeight: FontWeight.bold,
                                                fontSize: 13,
                                                letterSpacing: 0.5,
                                              ),
                                            ),
                                          ),
                                        ),
                                        const SizedBox(width: 12),
                                        InkWell(
                                          onTap: () =>
                                              _deleteActivity(activity),
                                          borderRadius: BorderRadius.circular(
                                            4,
                                          ),
                                          child: const Padding(
                                            padding: EdgeInsets.symmetric(
                                              horizontal: 8,
                                              vertical: 4,
                                            ),
                                            child: Text(
                                              'DELETE',
                                              style: TextStyle(
                                                color: Colors.redAccent,
                                                fontWeight: FontWeight.bold,
                                                fontSize: 13,
                                                letterSpacing: 0.5,
                                              ),
                                            ),
                                          ),
                                        ),
                                      ],
                                    ),
                                  ],
                                ),
                              ),
                            ],
                          ),
                        ),
                      );
                    },
                  ),
          ),
        ],
      ),
      floatingActionButton: FloatingActionButton(
        onPressed: () => _showActivityForm(),
        backgroundColor: Colors.orangeAccent,
        foregroundColor: Colors.white,
        elevation: 3,
        shape: RoundedRectangleBorder(borderRadius: BorderRadius.circular(16)),
        child: const Icon(Icons.add, size: 28),
      ),
    );
  }
}
