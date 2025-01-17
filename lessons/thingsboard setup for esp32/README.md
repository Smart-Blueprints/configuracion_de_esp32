# Steps for configuring ThingsBoard and programming ESP32

## 1. Create a free ThingsBoard account
- **Create a temporary email**:
  - Visit [Temp-Mail](https://temp-mail.org/en/).
  - Copy the disposable email address provided when opening the page.
  ![Creating a temporary email](images/creating-temporary-email.png)

- **Register on ThingsBoard Cloud**:
  - Go to the [ThingsBoard Cloud sign-up page](https://thingsboard.cloud/signup).
  - Fill in the required details to create an account.
  ![Create ThingBoard account](images/create-thingboard-account.png)

- **Verify your email**:
  - Check the verification email sent to the temporary email address.
  ![Verify email](images/verify-email.png)

  - Click the "Activate Your Account" button.
  ![Activate ThingsBoard account](images/activate-thingsboard-account.png)

- **Login to ThingsBoard**:
  - After activation, click the "Login" button to access your ThingsBoard account.

---

## 2. Configure the ThingsBoard Account
- **Create a Device**:
  - Navigate to **Entities > Devices**.
  ![Thingsboard entities panel](images/thingsboard-entities-panel.png)

  - Create a new device representing the smart home.
  ![Create new device](images/create-new-device.png)

  - Add a name for the device and click **Add**.
  ![Naming the new device](images/naming-the-new-device.png)

  - Close the pop-up window, click on the newly created device, and copy the **access token** for linking it to your program.
  ![Copy the access token](images/copy-access-token.png)

- **Set Up the Dashboard**:
  - Go to the **Dashboards** section.
   ![Dashboard panel](images/dashboard-panel.png)

  - Import a pre-made dashboard for visualizing parameters and controlling the smart home:
   ![Import dashboard](images/import-dashboard.png)

    1. Drag and drop the `smarthome.json` file (provided in the class folder) to the indicated area.
    2. Click the **Import** button.
  ![Drag and drop config file](images/drag-and-drop-config-file.png)

  - Open the newly imported dashboard (note: data may not appear initially).
  ![Open imported dashboard](images/open-imported-dashboard.png)

  - Enter the **Edit Mode** of the dashboard.
  ![Dashboard edit mode](images/dashboard-edit-mode.png)

  - For each widget, go to its **property editor**:
  ![Property editor](images/property-editor.png)

    1. Link the widget to the previously created device.
  ![Link widget to device](images/link-widget-to-device.png)

    2. Repeat for all widgets.
  - After linking all widgets to the device, click **Save**.
  ![Save linked devices](images/save-linked.devices.png)

---

## 3. Program the ESP32 to Connect to ThingsBoard
- **Create a WiFi Hotspot**:
  - Use a mobile phone with a stable internet connection to create a WiFi access point.
  - The ESP32 will connect to this hotspot to communicate with ThingsBoard.

- **Open the Project Code**:
  - Locate the `smart-home-project-TB` code provided in the class folder.
  - Modify the following lines in the code:
    1. Replace the placeholder WiFi name and password with the details of the hotspot you created earlier.
    ![Update wifi and password](images/update-wifi-and-password.png)

    2. Update the **access token** with the token from the device created in ThingsBoard.
    ![Update access token](images/update-access-token.png)

- **Visualize Data on the Dashboard**:
  - Open the configured ThingsBoard dashboard to monitor home parameters and control devices.
