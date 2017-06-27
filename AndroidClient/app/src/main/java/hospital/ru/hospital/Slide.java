package hospital.ru.hospital;

import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.os.AsyncTask;
import android.os.Bundle;
import android.os.StrictMode;
import android.support.annotation.Nullable;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.util.Log;
import android.view.View;
import android.support.design.widget.NavigationView;
import android.support.v4.view.GravityCompat;
import android.support.v4.widget.DrawerLayout;
import android.support.v7.app.ActionBarDrawerToggle;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.TextView;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;

import org.apache.http.*;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.BasicResponseHandler;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;


public class Slide extends AppCompatActivity
        implements NavigationView.OnNavigationItemSelectedListener {

    private boolean hasToken = false;
    private boolean hasAuth = false;
    private Profile profile;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //
        setContentView(R.layout.content_slide_auth);

        StrictMode.ThreadPolicy policy = new StrictMode.ThreadPolicy.Builder().permitAll().build();

        StrictMode.setThreadPolicy(policy);
        Button button = (Button) findViewById(R.id.login);

        button.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                String polis = ((TextView) findViewById(R.id.polis)).getText().toString();
                String password = ((TextView) findViewById(R.id.password)).getText().toString();
                String token = auth(polis, password);
                if (token != null) {
                    hasAuth = true;
                    profile = new Profile(token);
                    writeTokenFile(token);
                    initInterface();
                }
            }
        });
        if (exitsTokenFile()) {
            String token = readTokenFile();
            if (token != null) {
                try {
                    hasAuth = checkToken(token);


                    if (hasAuth) {
                        profile = new Profile(token);
                        initInterface();
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            }
        } else {
            hasToken = false;
        }

    }

    @Override
    public void onBackPressed() {
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        if (drawer.isDrawerOpen(GravityCompat.START)) {
            drawer.closeDrawer(GravityCompat.START);
        } else {
            super.onBackPressed();
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.slide, menu);
        ImageView image = (ImageView) findViewById(R.id.imageView);
        if (image != null) {
            DownloadImageTask d = new DownloadImageTask(image);
            d.execute(profile.getURLImage());
        }
        TextView text = (TextView) findViewById(R.id.FIO);
        if (text != null) {
            text.setText(profile.getName());
            ((TextView) findViewById(R.id.contactInfo)).setText(profile.getEmail() + " " + profile.getPhone());


        }
       /*MenuItem polis = (MenuItem) findViewById(R.id.polisItem);
        if (polis!=null){
            polis.setTitle(profile.getPolis());
            ((MenuItem) findViewById(R.id.dateAlive)).setTitle(profile.getDate());
        }else{
            Log.e("asd",profile.getPolis());
        }
*/
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();

        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            writeTokenFile("E");
            System.exit(0);
            finish();
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @SuppressWarnings("StatementWithEmptyBody")
    @Override
    public boolean onNavigationItemSelected(MenuItem item) {
        // Handle navigation view item clicks here.
        int id = item.getItemId();

        if (id == R.id.records) {
            ListView list = (ListView) findViewById(R.id.List);

            JSONObject jsonObject = null;
            try {
                try {
                    jsonObject = new JSONObject(getRecords());
                } catch (JSONException e) {
                    e.printStackTrace();
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
            if (jsonObject == null) return false;
            try {
                JSONArray jArray = jsonObject.getJSONArray("data");
                ArrayList<String> array = new ArrayList<>();
                for (int i = 0; i < jArray.length(); i++) {
                    JSONObject jObject = jArray.getJSONObject(i);
                    array.add(
                            jObject.getString("d_first_name").charAt(0) + "." + jObject.getString("d_middle_name").charAt(0) + ". " + jObject.getString("d_second_name") + " (" +
                                    jObject.getString("post_name") + ") " + jObject.getString("date"));

                }

                ArrayAdapter<String> adapter = new ArrayAdapter<>(this,
                        android.R.layout.simple_list_item_1, array);
                list.setAdapter(adapter);

            } catch (JSONException e) {
                e.printStackTrace();
            }


        } else if (id == R.id.history) {
            try {
                ListView list = (ListView) findViewById(R.id.List);

                JSONObject jsonObject = new JSONObject(getHistory());
                JSONArray jArray = jsonObject.getJSONArray("data");
                ArrayList<String> array = new ArrayList<>();
                for (int i = 0; i < jArray.length(); i++) {
                    JSONObject jObject = jArray.getJSONObject(i);
                    array.add(
                            jObject.getString("text")+" (" + jObject.getString("date")+")");

                }

                ArrayAdapter<String> adapter = new ArrayAdapter<>(this,
                        android.R.layout.simple_list_item_1, array);
                list.setAdapter(adapter);
            } catch (IOException e) {
                e.printStackTrace();
            } catch (JSONException e) {
                e.printStackTrace();
            }
        }

        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        drawer.closeDrawer(GravityCompat.START);
        return true;
    }

    public String auth(String name, String password) {
        HttpClient httpclient = new DefaultHttpClient();
        HttpPost http = new HttpPost("http://194.87.98.46/hospital/server/request/auth/");
        List nameValuePairs = new ArrayList(2);
        nameValuePairs.add(new BasicNameValuePair("name", name));
        nameValuePairs.add(new BasicNameValuePair("password", password));
        try {
            http.setEntity(new UrlEncodedFormEntity(nameValuePairs));
            String response = (String) httpclient.execute(http, new BasicResponseHandler());
            JSONObject jsonObject = new JSONObject(response);

            if (jsonObject.getInt("level") == 0) {
                return jsonObject.getJSONObject("data").getString("token");
            }
            return null;
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (JSONException e) {
            e.printStackTrace();
        }
        return null;
    }


    public String getRecords() throws IOException {

        HttpClient httpclient = new DefaultHttpClient();
        HttpPost http = new HttpPost("http://194.87.98.46/hospital/server/request/getListDoctors/");
        List nameValuePairs = new ArrayList(2);
        nameValuePairs.add(new BasicNameValuePair("token", profile.getToken()));
        try {
            http.setEntity(new UrlEncodedFormEntity(nameValuePairs));
            String response = (String) httpclient.execute(http, new BasicResponseHandler());
            Log.e("Return ", response);
            return response;
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        return "";
    }

    public String getHistory() throws IOException {

        HttpClient httpclient = new DefaultHttpClient();
        HttpPost http = new HttpPost("http://194.87.98.46/hospital/server/request/getPersonalHistory/");
        List nameValuePairs = new ArrayList(2);
        nameValuePairs.add(new BasicNameValuePair("token", profile.getToken()));
        try {
            http.setEntity(new UrlEncodedFormEntity(nameValuePairs));
            String response = (String) httpclient.execute(http, new BasicResponseHandler());
            Log.e("Return ", response);
            return response;
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        return "";
    }

    public void initInterface() {
        setContentView(R.layout.activity_slide);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);
        DrawerLayout drawer = (DrawerLayout) findViewById(R.id.drawer_layout);
        ActionBarDrawerToggle toggle = new ActionBarDrawerToggle(
                this, drawer, toolbar, R.string.navigation_drawer_open, R.string.navigation_drawer_close);
        drawer.setDrawerListener(toggle);
        toggle.syncState();
        NavigationView navigationView = (NavigationView) findViewById(R.id.nav_view);
        navigationView.setNavigationItemSelectedListener(this);
    }

    void writeTokenFile(String token) {
        try {
            // отрываем поток для записи
            BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(
                    openFileOutput("token", MODE_PRIVATE)));
            // пишем данные
            bw.write(token);
            // закрываем поток
            bw.close();
            Log.d("Token", "Файл записан");
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public boolean exitsTokenFile() {
        try {
            new BufferedReader(new InputStreamReader(
                    openFileInput("token")));
            return true;
        } catch (FileNotFoundException e) {
            return false;
        }
    }

    public String readTokenFile() {
        try {
            // открываем поток для чтения
            BufferedReader br = new BufferedReader(new InputStreamReader(
                    openFileInput("token")));
            String str = "";
            // читаем содержимое
            while ((str = br.readLine()) != null) {
                Log.d("Token", str);
                return str;
            }
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    public boolean checkToken(String token) throws IOException, JSONException {
        HttpClient httpclient = new DefaultHttpClient();
        HttpPost http = new HttpPost("http://194.87.98.46/hospital/server/request/getProfile/");
        List nameValuePairs = new ArrayList(1);
        nameValuePairs.add(new BasicNameValuePair("token", token));
        try {
            http.setEntity(new UrlEncodedFormEntity(nameValuePairs));
            String response = (String) httpclient.execute(http, new BasicResponseHandler());
            JSONObject jsonObject = new JSONObject(response);

            return jsonObject.getInt("level") == 0;
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        return false;
    }
}

class DownloadImageTask extends AsyncTask<String, Void, Bitmap> {
    ImageView bmImage;

    public DownloadImageTask(ImageView bmImage) {
        this.bmImage = bmImage;
    }

    protected Bitmap doInBackground(String... urls) {
        String urldisplay = urls[0];
        Bitmap mIcon11 = null;
        try {
            InputStream in = new java.net.URL(urldisplay).openStream();
            mIcon11 = BitmapFactory.decodeStream(in);
        } catch (Exception e) {
            Log.e("Error", e.getMessage());
            e.printStackTrace();
        }
        return mIcon11;
    }

    protected void onPostExecute(Bitmap result) {
        bmImage.setImageBitmap(result);
    }
}

class Profile {

    private String token;
    private Boolean init = false;
    private String image = "";
    private String email = "";
    private String phone = "";
    private String fullName = "";
    private String date = "";
    private String polis = "";

    public Profile(String token) {
        this.token = token;
        initProfile();
    }

    private void initProfile() {
        HttpClient httpclient = new DefaultHttpClient();
        HttpPost http = new HttpPost("http://194.87.98.46/hospital/server/request/getProfile/");
        List nameValuePairs = new ArrayList(1);
        nameValuePairs.add(new BasicNameValuePair("token", token));
        try {
            http.setEntity(new UrlEncodedFormEntity(nameValuePairs));
            String response = (String) httpclient.execute(http, new BasicResponseHandler());
            JSONObject jsonObject = new JSONObject(response);

            init = jsonObject.getInt("level") == 0;
            if (init) {
                JSONObject data = jsonObject.getJSONObject("data");
                fullName = data.getString("first_name") + " " + data.getString("middle_name") + " "
                        + data.getString("second_name");
                image = data.getString("photo");
                email = data.getString("email");
                phone = data.getString("phone");
                polis = data.getString("polis");
                date = data.getString("date");
            }
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        } catch (JSONException e) {
            e.printStackTrace();
        }
    }

    public String getName() {
        return this.fullName;
    }

    public String getEmail() {
        return email;
    }

    public String getURLImage() {
        return image;
    }

    public String getPhone() {
        return phone;
    }

    public String getToken() {
        return token;
    }

    public String getDate() {
        return date;
    }

    public String getPolis() {
        return polis;
    }
}
